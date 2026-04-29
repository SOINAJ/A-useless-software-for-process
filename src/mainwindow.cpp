#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "processmanager.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QStatusBar>
#include <QMessageBox>
#include <QLabel>
#include <QRadioButton>
#include <QComboBox>
#include <QPushButton>
#include <algorithm>

#include "filetools.h"

#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>

// ────────────────────────────────────────────────────────────────
// Construction
// ────────────────────────────────────────────────────────────────

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    m_logicalCores = ProcessManager::logicalProcessorCount();
    m_physicalCores = ProcessManager::physicalCoreCount();

    ui = new Ui::MainWindow();
    ui->setupUi(this);

    setupDynamicUi();
    applyStylesheet();
    refreshProcessList();

    m_refreshTimer = new QTimer(this);
    m_refreshTimer->setInterval(m_refreshMs);
    connect(m_refreshTimer, &QTimer::timeout, this, &MainWindow::refreshProcessList);
    m_refreshTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ────────────────────────────────────────────────────────────────
// Dynamic UI — everything the .ui file can't express
// ────────────────────────────────────────────────────────────────

void MainWindow::setupDynamicUi()
{
    // ── Admin badge — dynamic text + objectName ──
    bool isAdmin = ProcessManager::isRunAsAdmin();
    ui->adminBadgeLabel->setText(isAdmin
        ? QStringLiteral("●  Administrator Elevated")
        : QStringLiteral("●  Limited (not admin)"));
    ui->adminBadgeLabel->setObjectName(isAdmin
        ? QStringLiteral("adminBadgeOk") : QStringLiteral("adminBadgeWarn"));

    // ── Status bar permanent widgets ──
    auto* coreInfo = new QLabel(
        QStringLiteral("Logical: %1   Physical: %2   ")
            .arg(m_logicalCores).arg(m_physicalCores));
    coreInfo->setObjectName(QStringLiteral("coreInfo"));
    statusBar()->addPermanentWidget(coreInfo);

    auto* actionLabel = new QLabel;
    actionLabel->setObjectName(QStringLiteral("actionLabel"));
    statusBar()->addPermanentWidget(actionLabel);

    // ── Splitter stretch ──
    ui->splitter->setStretchFactor(0, 6);
    ui->splitter->setStretchFactor(1, 4);

    // ── Table column config ──
    ui->processTable->setHorizontalHeaderLabels({
        QString(), QStringLiteral("PID"),
        QStringLiteral("Process Name"),
        QStringLiteral("Priority"),
        QStringLiteral("Affinity"),
        QStringLiteral("Memory") });
    ui->processTable->horizontalHeader()->setStretchLastSection(true);
    ui->processTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->processTable->setColumnWidth(0, 48);
    ui->processTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->processTable->setColumnWidth(1, 90);
    ui->processTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->processTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->processTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    ui->processTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    ui->processTable->setColumnWidth(5, 120);

    // ── Priority QButtonGroup ──
    m_priorityGroup = new QButtonGroup(this);

    struct { QRadioButton* btn; DWORD val; const char* hint; } priDefs[] = {
        { ui->realtimeRadio,       REALTIME_PRIORITY_CLASS,     "Reserved for critical sub-systems" },
        { ui->highRadio,           HIGH_PRIORITY_CLASS,         nullptr },
        { ui->aboveNormalRadio,    ABOVE_NORMAL_PRIORITY_CLASS, nullptr },
        { ui->normalRadio,         NORMAL_PRIORITY_CLASS,       nullptr },
        { ui->belowNormalRadio,    BELOW_NORMAL_PRIORITY_CLASS, nullptr },
        { ui->idleRadio,           IDLE_PRIORITY_CLASS,         nullptr },
    };

    for (const auto& def : priDefs) {
        if (def.hint)
            def.btn->setToolTip(QString::fromLatin1(def.hint));
        m_priorityGroup->addButton(def.btn, static_cast<int>(def.val));
    }

    connect(m_priorityGroup,
            QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
            this, [this]() { onPriorityChanged(); });

    // ── Affinity checkbox grid (core-count dependent) ──
    auto* affGrid = new QGridLayout;
    affGrid->setSpacing(6);
    int cols = 4;
    for (int i = 0; i < m_logicalCores; ++i) {
        auto* cb = new QCheckBox(QString::number(i));
        cb->setChecked(true);
        cb->setObjectName(QStringLiteral("affCheck"));
        connect(cb, &QCheckBox::toggled, this, &MainWindow::onAffinityToggled);
        affGrid->addWidget(cb, i / cols, i % cols);
        m_affinityChecks.append(cb);
    }
    // Insert at position 0 (quickRow at position 1 in the .ui file)
    auto* affLayout = static_cast<QVBoxLayout*>(ui->affinityGroupBox->layout());
    affLayout->insertLayout(0, affGrid, 0);

    // ── Signal / Slot connections ──
    connect(ui->refreshButton, &QPushButton::clicked,
            this, &MainWindow::refreshProcessList);
    connect(ui->speedButton, &QPushButton::clicked,
            this, [this]() {
                m_refreshMs = (m_refreshMs == 1000) ? 5000 : 1000;
                m_refreshTimer->setInterval(m_refreshMs);
                ui->speedButton->setText(QStringLiteral("Refresh (%1s)").arg(m_refreshMs / 1000));
            });
    connect(ui->selectAllCheckBox, &QCheckBox::toggled,
            this, &MainWindow::onSelectAllToggled);
    connect(ui->processTable, &QTableWidget::itemChanged,
            this, &MainWindow::onProcessChecked);
    connect(ui->searchLineEdit, &QLineEdit::textChanged,
            this, &MainWindow::onSearchChanged);
    connect(ui->selectAllCoresButton, &QPushButton::clicked,
            this, &MainWindow::onSelectAllCores);
    connect(ui->selectPhysicalCoresButton, &QPushButton::clicked,
            this, &MainWindow::onSelectPhysicalCores);
    connect(ui->clearCoresButton, &QPushButton::clicked,
            this, &MainWindow::onClearCores);
    connect(ui->applyButton, &QPushButton::clicked,
            this, &MainWindow::onApply);
    connect(ui->typeConfigButton, &QPushButton::clicked,
            this, &MainWindow::openType);

    // ── Filter type combo (user-added widget) ──
    loadProcessItems();
}

void MainWindow::loadProcessItems()
{
    QString dir = QCoreApplication::applicationDirPath();
    QString filePath = dir + QStringLiteral("/processItem.txt");

    auto readStream = FileTools::openStream(filePath);
    if (!readStream) {
        qDebug() << "processItem.txt 打开失败:" << filePath;
        return;
    }

    QString currentKey;

    QString line;
    while (readStream->readLineInto(&line)) {
        line = line.trimmed();
        if (line.isEmpty()) continue;

        if (line.startsWith("#")) {
            currentKey = line.mid(1).trimmed();
            allProcessData[currentKey] = QStringList();

        } else if (line.startsWith("::") && !currentKey.isEmpty()) {
            QString value = line.mid(2).trimmed();
            allProcessData[currentKey].append(value);
        }
    }

    // 清空旧数据，避免重复添加
    ui->filterTypeComboBox->clear();

    // 添加固定选项
    ui->filterTypeComboBox->addItem(QStringLiteral("All Processes"));
//    ui->filterTypeComboBox->addItem(QStringLiteral("System Processes"));

    // 添加文件中的 key
    for (auto it = allProcessData.begin(); it != allProcessData.end(); ++it) {
        qDebug() << "#" << it.key() << "count:" << it.value().size();
        ui->filterTypeComboBox->addItem(it.key());  // 直接传 QString，不要 QStringLiteral
    }

    // 信号槽只绑定一次，建议放到构造函数里，不要每次加载都绑定
    // 如果必须在这里绑定，先断开旧连接
    disconnect(ui->filterTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
               this, &MainWindow::onFilterTypeChanged);
    connect(ui->filterTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onFilterTypeChanged);
}

// ────────────────────────────────────────────────────────────────
// Process table population
// ────────────────────────────────────────────────────────────────

void MainWindow::populateTable()
{
    QSet<DWORD> livePids;
    for (const auto& p : m_allProcesses)
        livePids.insert(p.pid);
    m_selectedPids.intersect(livePids);

    ui->processTable->setUpdatesEnabled(false);
    ui->processTable->blockSignals(true);
    ui->processTable->setRowCount(0);

    QString filter = ui->searchLineEdit->text().trimmed().toLower();
    int logicalCount = m_logicalCores;

    auto processOrder = m_allProcesses;
    if (filter.isEmpty() && !m_selectedPids.isEmpty()) {
        std::stable_partition(processOrder.begin(), processOrder.end(),
            [&](const ProcessInfo& p) { return m_selectedPids.contains(p.pid); });
    }

    int displayed = 0;
    int comboIndex = ui->filterTypeComboBox->currentIndex();
    for (const auto& proc : processOrder) {
        // Type filter first — narrow to the selected category
        if (comboIndex > 0) {
            QString key = ui->filterTypeComboBox->currentText();
            const QStringList& names = allProcessData.value(key);
            // Match if proc.name starts with any configured name (case-insensitive).
            // This handles e.g. config "Sguard" matching "SGuard.exe", "SGuardSvc.exe", etc.
            auto nameMatches = [&](const QString& n) {
                return proc.name.startsWith(n, Qt::CaseInsensitive);
            };
            if (std::none_of(names.begin(), names.end(), nameMatches))
                continue;
        }

        // Search filter — search by name or PID within the type-filtered set
        if (!filter.isEmpty()) {
            bool match = proc.name.toLower().contains(filter)
                      || QString::number(proc.pid).contains(filter);
            if (match) {
                qDebug() << "MATCH:" << proc.name << "filter:" << filter;
            }
            if (!match) continue;
        }

        int r = ui->processTable->rowCount();
        ui->processTable->insertRow(r);
        ++displayed;

        // Col 0 — checkbox
        auto* chkItem = new QTableWidgetItem;
        chkItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        chkItem->setCheckState(m_selectedPids.contains(proc.pid) ? Qt::Checked : Qt::Unchecked);
        chkItem->setData(Qt::UserRole, static_cast<uint>(proc.pid));
        ui->processTable->setItem(r, 0, chkItem);

        // Col 1 — PID
        auto* pidItem = new QTableWidgetItem(QString::number(proc.pid));
        pidItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->processTable->setItem(r, 1, pidItem);

        // Col 2 — Name
        QString nameText = proc.name;
        if (proc.isSystem)
            nameText += QStringLiteral("  🛡");
        auto* nameItem = new QTableWidgetItem(nameText);
        nameItem->setToolTip(proc.name);
        ui->processTable->setItem(r, 2, nameItem);

        // Col 3 — Priority badge
        QString priStr = priorityToString(proc.priority);
        auto* priItem = new QTableWidgetItem(priStr);
        priItem->setTextAlignment(Qt::AlignCenter);

        QColor bg, fg;
        switch (proc.priority) {
            case REALTIME_PRIORITY_CLASS:
                bg = QColor(QStringLiteral("#fee2e2")); fg = QColor(QStringLiteral("#991b1b")); break;
            case HIGH_PRIORITY_CLASS:
                bg = QColor(QStringLiteral("#ffedd5")); fg = QColor(QStringLiteral("#9a3412")); break;
            case ABOVE_NORMAL_PRIORITY_CLASS:
                bg = QColor(QStringLiteral("#dbeafe")); fg = QColor(QStringLiteral("#1e40af")); break;
            case BELOW_NORMAL_PRIORITY_CLASS:
                bg = QColor(QStringLiteral("#f1f5f9")); fg = QColor(QStringLiteral("#64748b")); break;
            case IDLE_PRIORITY_CLASS:
                bg = QColor(QStringLiteral("#f8fafc")); fg = QColor(QStringLiteral("#94a3b8")); break;
            default:
                bg = QColor(QStringLiteral("#f1f5f9")); fg = QColor(QStringLiteral("#475569")); break;
        }
        priItem->setBackground(bg);
        priItem->setForeground(fg);
        priItem->setData(Qt::UserRole, static_cast<uint>(proc.priority));
        ui->processTable->setItem(r, 3, priItem);

        // Col 4 — Affinity
        QString affStr;
        if (proc.affinity.size() == logicalCount)
            affStr = QStringLiteral("All Cores");
        else if (proc.affinity.isEmpty())
            affStr = QStringLiteral("—");
        else {
            QStringList sl;
            for (int c : proc.affinity)
                sl << QString::number(c);
            affStr = sl.join(QStringLiteral(", "));
        }
        ui->processTable->setItem(r, 4, new QTableWidgetItem(affStr));

        // Col 5 — Memory
        auto* memItem = new QTableWidgetItem(
            QStringLiteral("%1 MB").arg(proc.memoryMB, 0, 'f', 1));
        memItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->processTable->setItem(r, 5, memItem);
    }

    ui->processTable->blockSignals(false);
    ui->processTable->setUpdatesEnabled(true);

    ui->selectAllCheckBox->blockSignals(true);
    ui->selectAllCheckBox->setChecked(displayed > 0);
    ui->selectAllCheckBox->blockSignals(false);

    ui->processCountBadgeLabel->setText(QString::number(displayed));

    int selCount = 0;
    for (int r = 0; r < ui->processTable->rowCount(); ++r) {
        if (ui->processTable->item(r, 0)->checkState() == Qt::Checked)
            ++selCount;
    }
    ui->applyButton->setText(QStringLiteral("Apply to %1 Selected  →").arg(selCount));
    bool canApply = (selCount > 0) && (affinityMaskFromUi() != 0);
    ui->applyButton->setEnabled(canApply);
}

// ────────────────────────────────────────────────────────────────
// Slots
// ────────────────────────────────────────────────────────────────

void MainWindow::refreshProcessList()
{
    m_allProcesses = ProcessManager::enumerateProcesses();

    auto [totalRam, usedRam] = ProcessManager::systemMemory();
    ui->ramValueLabel->setText(QStringLiteral("%1 / %2 GB")
        .arg(usedRam, 0, 'f', 1).arg(totalRam, 0, 'f', 1));

    ui->cpuLoadValueLabel->setText(QStringLiteral("-- %"));

    populateTable();
}

void MainWindow::onSearchChanged(const QString& /*text*/)
{
    populateTable();
}

void MainWindow::onSelectAllToggled(bool checked)
{
    for (int r = 0; r < ui->processTable->rowCount(); ++r) {
        if (auto* item = ui->processTable->item(r, 0)) {
            item->setCheckState(checked ? Qt::Checked : Qt::Unchecked);
            DWORD pid = static_cast<DWORD>(item->data(Qt::UserRole).toUInt());
            if (checked)
                m_selectedPids.insert(pid);
            else
                m_selectedPids.remove(pid);
        }
    }
    int selCount = checked ? ui->processTable->rowCount() : 0;
    ui->applyButton->setText(QStringLiteral("Apply to %1 Selected  →").arg(selCount));
    bool canApply = (selCount > 0) && (affinityMaskFromUi() != 0);
    ui->applyButton->setEnabled(canApply);
}

void MainWindow::onProcessChecked(QTableWidgetItem* item)
{
    if (!item) return;
    DWORD pid = static_cast<DWORD>(item->data(Qt::UserRole).toUInt());
    if (item->checkState() == Qt::Checked)
        m_selectedPids.insert(pid);
    else
        m_selectedPids.remove(pid);

    int selCount = 0;
    for (int r = 0; r < ui->processTable->rowCount(); ++r) {
        if (ui->processTable->item(r, 0)->checkState() == Qt::Checked)
            ++selCount;
    }
    ui->applyButton->setText(QStringLiteral("Apply to %1 Selected  →").arg(selCount));
    bool canApply = (selCount > 0) && (affinityMaskFromUi() != 0);
    ui->applyButton->setEnabled(canApply);

    ui->selectAllCheckBox->blockSignals(true);
    ui->selectAllCheckBox->setChecked(selCount == ui->processTable->rowCount() && selCount > 0);
    ui->selectAllCheckBox->blockSignals(false);
}

void MainWindow::onPriorityChanged() {}

void MainWindow::onAffinityToggled()
{
    int mask = affinityMaskFromUi();
    int selCount = 0;
    for (int r = 0; r < ui->processTable->rowCount(); ++r) {
        if (ui->processTable->item(r, 0)->checkState() == Qt::Checked)
            ++selCount;
    }
    bool canApply = (mask != 0) && (selCount > 0);
    ui->applyButton->setEnabled(canApply);
    ui->applyButton->setText(QStringLiteral("Apply to %1 Selected  →").arg(selCount));
}

void MainWindow::openType()
{
    QString filePath = QCoreApplication::applicationDirPath() + QStringLiteral("/processItem.txt");
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void MainWindow::onSelectAllCores()
{
    for (auto* cb : m_affinityChecks)
        cb->setChecked(true);
}

void MainWindow::onSelectPhysicalCores()
{
    for (int i = 0; i < m_affinityChecks.size(); ++i)
        m_affinityChecks[i]->setChecked(i < m_physicalCores);
}

void MainWindow::onClearCores()
{
    for (auto* cb : m_affinityChecks)
        cb->setChecked(false);
}

void MainWindow::onFilterTypeChanged(int /*index*/)
{
    // Re-filter the table when user picks a different process type
    populateTable();
}

int MainWindow::affinityMaskFromUi() const
{
    QVector<int> cores;
    for (int i = 0; i < m_affinityChecks.size(); ++i) {
        if (m_affinityChecks[i]->isChecked())
            cores.append(i);
    }
    return static_cast<int>(ProcessManager::coresToMask(cores));
}

void MainWindow::onApply()
{
    QVector<DWORD> selectedPids;
    for (int r = 0; r < ui->processTable->rowCount(); ++r) {
        auto* item = ui->processTable->item(r, 0);
        if (item && item->checkState() == Qt::Checked)
            selectedPids.append(static_cast<DWORD>(item->data(Qt::UserRole).toUInt()));
    }
    if (selectedPids.isEmpty()) return;

    DWORD newPri = static_cast<DWORD>(m_priorityGroup->checkedId());
    QVector<int> affCores;
    for (int i = 0; i < m_affinityChecks.size(); ++i) {
        if (m_affinityChecks[i]->isChecked())
            affCores.append(i);
    }

    bool hasSystem = false;
    for (DWORD pid : selectedPids) {
        if (pid == 0 || pid == 4) { hasSystem = true; break; }
    }
    if (hasSystem || newPri == REALTIME_PRIORITY_CLASS) {
        auto answer = QMessageBox::warning(this,
            QStringLiteral("Warning"),
            QStringLiteral("Modifying system processes or setting 'Realtime' priority "
                           "can cause system instability.\n\nContinue?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (answer != QMessageBox::Yes) return;
    }

    if (!ProcessManager::isRunAsAdmin()) {
        QMessageBox::warning(this,
            QStringLiteral("Insufficient Permissions"),
            QStringLiteral("Not running as Administrator.\n\n"
                           "Modifying other processes' priority or affinity "
                           "requires Administrator privileges.\n\n"
                           "Please restart ProcessWarden as Administrator."));
        return;
    }

    QStringList errors;
    int okCount = 0;
    for (DWORD pid : selectedPids) {
        bool priOk = true, affOk = true;
        QString procName;
        for (const auto& p : m_allProcesses) {
            if (p.pid == pid) { procName = p.name; break; }
        }

        if (newPri != 0) {
            priOk = ProcessManager::setProcessPriority(pid, newPri);
            if (!priOk)
                errors << QStringLiteral("%1 (PID %2): priority — %3")
                    .arg(procName).arg(pid)
                    .arg(ProcessManager::lastErrorString());
        }

        if (!affCores.isEmpty()) {
            affOk = ProcessManager::setProcessAffinity(pid, affCores);
            if (!affOk)
                errors << QStringLiteral("%1 (PID %2): affinity — %3")
                    .arg(procName).arg(pid)
                    .arg(ProcessManager::lastErrorString());
        }

        if (priOk && affOk) ++okCount;
    }

    if (okCount == selectedPids.size()) {
        m_selectedPids.clear();
        statusBar()->showMessage(
            QStringLiteral("Success — updated %1 process(es)").arg(okCount), 5000);
    } else {
        statusBar()->showMessage(
            QStringLiteral("FAILED: %1 / %2 succeeded").arg(okCount).arg(selectedPids.size()), 0);
        if (!errors.isEmpty()) {
            QMessageBox::critical(this,
                QStringLiteral("Operation Failed"),
                errors.join(QStringLiteral("\n")));
        }
    }

    refreshProcessList();
}

// ────────────────────────────────────────────────────────────────
// Stylesheet
// ────────────────────────────────────────────────────────────────

void MainWindow::applyStylesheet()
{
    setStyleSheet(QStringLiteral(R"(
        QMainWindow {
            background: #f1f5f9;
        }

        /* Header */
        #header {
            background: #ffffff;
            border-bottom: 1px solid #e2e8f0;
        }
        #headerIcon {
            background: #2563eb;
            color: #ffffff;
            border-radius: 8px;
            font-size: 28px;
            font-weight: bold;
        }
        #headerTitle {
            font-size: 24px;
            font-weight: bold;
            color: #0f172a;
        }
        #headerVersion {
            font-size: 24px;
            font-weight: normal;
            color: #94a3b8;
        }
        #adminBadgeOk {
            font-size: 16px;
            font-weight: bold;
            color: #059669;
            text-transform: uppercase;
        }
        #adminBadgeWarn {
            font-size: 16px;
            font-weight: bold;
            color: #d97706;
            text-transform: uppercase;
        }
        #sysTitle {
            font-size: 16px;
            font-weight: bold;
            color: #94a3b8;
            text-transform: uppercase;
        }
        #sysValue {
            font-size: 20px;
            font-weight: bold;
            color: #1e293b;
            font-family: "JetBrains Mono", "Consolas", monospace;
        }

        /* Panels */
        #panel, #controlPanel {
            background: transparent;
        }
        #sectionTitle {
            font-size: 16px;
            font-weight: bold;
            color: #94a3b8;
            text-transform: uppercase;
        }
        #badge {
            font-size: 16px;
            font-weight: bold;
            color: #475569;
            background: #e2e8f0;
            border-radius: 10px;
            padding: 2px 10px;
        }

        /* Table */
        #processTable {
            background: #ffffff;
            border: 1px solid #e2e8f0;
            border-radius: 8px;
            gridline-color: transparent;
            font-size: 18px;
        }
        #processTable::item {
            padding: 8px 10px;
            border-bottom: 1px solid #f1f5f9;
        }
        #processTable::item:selected {
            background: #eff6ff;
            color: inherit;
        }
        QHeaderView::section {
            background: #f8fafc;
            border: none;
            border-bottom: 1px solid #e2e8f0;
            padding: 10px 10px;
            font-size: 16px;
            font-weight: bold;
            color: #94a3b8;
            text-transform: uppercase;
        }

        /* Control groups */
        #ctrlGroup {
            background: #ffffff;
            border: 1px solid #e2e8f0;
            border-radius: 8px;
            margin-top: 0;
            padding: 14px;
            font-size: 16px;
            font-weight: bold;
            color: #94a3b8;
            text-transform: uppercase;
        }
        #ctrlGroup::title {
            subcontrol-origin: margin;
            left: 12px;
            padding: 0 4px;
        }

        /* Search */
        QLineEdit {
            padding: 10px 14px;
            border: 1px solid #e2e8f0;
            border-radius: 8px;
            background: #f8fafc;
            font-size: 20px;
            color: #1e293b;
        }
        QLineEdit:focus {
            border-color: #2563eb;
            background: #ffffff;
        }

        /* Combo box */
        QComboBox {
            font-size: 16px;
            color: #1e293b;
        }
        /* Radio buttons */
        #priRadio {
            font-size: 20px;
            color: #334155;
            spacing: 8px;
            padding: 8px 10px;
        }

        /* Affinity checkboxes */
        #affCheck {
            font-size: 18px;
            font-weight: bold;
            spacing: 8px;
            padding: 6px 10px;
        }

        /* Buttons */
        #smallBtn {
            padding: 8px 14px;
            background: #f1f5f9;
            border: 1px solid #e2e8f0;
            border-radius: 6px;
            font-size: 16px;
            font-weight: bold;
            color: #475569;
        }
        #smallBtn:hover {
            background: #e2e8f0;
        }
        #applyBtn {
            padding: 14px;
            background: #2563eb;
            border: none;
            border-radius: 10px;
            font-size: 24px;
            font-weight: bold;
            color: #ffffff;
        }
        #applyBtn:hover {
            background: #1d4ed8;
        }
        #applyBtn:disabled {
            background: #e2e8f0;
            color: #94a3b8;
        }

        /* Status bar */
        QStatusBar {
            background: #1e293b;
            border: none;
            padding: 0;
        }
        #statusLabel {
            font-size: 16px;
            color: #10b981;
        }
        #coreInfo {
            font-size: 16px;
            color: #94a3b8;
        }
        #actionLabel {
            font-size: 16px;
            font-weight: bold;
            color: #34d399;
        }

        /* Splitter */
        QSplitter::handle {
            background: #e2e8f0;
        }
    )"));
}
