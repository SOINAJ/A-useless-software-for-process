/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QWidget *headerWidget;
    QHBoxLayout *headerLayout;
    QHBoxLayout *leftBox;
    QLabel *headerIconLabel;
    QVBoxLayout *titleBox;
    QLabel *headerTitleLabel;
    QLabel *headerVersionLabel;
    QSpacerItem *leftBoxSpacer;
    QLabel *adminBadgeLabel;
    QSpacerItem *headerStretch;
    QHBoxLayout *infoBox;
    QVBoxLayout *cpuLabel;
    QLabel *cpuLoadTitleLabel;
    QLabel *cpuLoadValueLabel;
    QVBoxLayout *ramLabelBox;
    QLabel *ramTitleLabel;
    QLabel *ramValueLabel;
    QSplitter *splitter;
    QWidget *processPanelWidget;
    QVBoxLayout *processPanelLayout;
    QHBoxLayout *toolbar;
    QLabel *monitorTitleLabel;
    QLabel *processCountBadgeLabel;
    QSpacerItem *toolbarSpacer;
    QPushButton *refreshButton;
    QPushButton *speedButton;
    QHBoxLayout *typeitem;
    QLabel *filterTypeLabel;
    QSpacerItem *typeitemSpacer;
    QComboBox *filterTypeComboBox;
    QPushButton *typeConfigButton;
    QCheckBox *selectAllCheckBox;
    QTableWidget *processTable;
    QWidget *controlPanelWidget;
    QVBoxLayout *controlPanelLayout;
    QGroupBox *searchGroupBox;
    QVBoxLayout *searchLayout;
    QLineEdit *searchLineEdit;
    QGroupBox *priorityGroupBox;
    QVBoxLayout *priorityLayout;
    QRadioButton *realtimeRadio;
    QRadioButton *highRadio;
    QRadioButton *aboveNormalRadio;
    QRadioButton *normalRadio;
    QRadioButton *belowNormalRadio;
    QRadioButton *idleRadio;
    QGroupBox *affinityGroupBox;
    QVBoxLayout *affinityLayout;
    QHBoxLayout *quickRow;
    QPushButton *selectAllCoresButton;
    QPushButton *selectPhysicalCoresButton;
    QPushButton *clearCoresButton;
    QPushButton *applyButton;
    QSpacerItem *controlPanelSpacer;
    QStatusBar *statusBar;
    QLabel *statusBarLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1400, 900);
        MainWindow->setMinimumSize(QSize(1000, 650));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->setSpacing(0);
        mainLayout->setContentsMargins(11, 11, 11, 11);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        headerWidget = new QWidget(centralWidget);
        headerWidget->setObjectName(QString::fromUtf8("headerWidget"));
        headerWidget->setMinimumSize(QSize(0, 80));
        headerWidget->setMaximumSize(QSize(16777215, 80));
        headerLayout = new QHBoxLayout(headerWidget);
        headerLayout->setSpacing(6);
        headerLayout->setContentsMargins(11, 11, 11, 11);
        headerLayout->setObjectName(QString::fromUtf8("headerLayout"));
        headerLayout->setContentsMargins(16, 0, 16, 0);
        leftBox = new QHBoxLayout();
        leftBox->setSpacing(10);
        leftBox->setObjectName(QString::fromUtf8("leftBox"));
        headerIconLabel = new QLabel(headerWidget);
        headerIconLabel->setObjectName(QString::fromUtf8("headerIconLabel"));
        headerIconLabel->setMinimumSize(QSize(48, 48));
        headerIconLabel->setMaximumSize(QSize(48, 48));
        headerIconLabel->setAlignment(Qt::AlignCenter);

        leftBox->addWidget(headerIconLabel);

        titleBox = new QVBoxLayout();
        titleBox->setSpacing(0);
        titleBox->setObjectName(QString::fromUtf8("titleBox"));
        headerTitleLabel = new QLabel(headerWidget);
        headerTitleLabel->setObjectName(QString::fromUtf8("headerTitleLabel"));

        titleBox->addWidget(headerTitleLabel);

        headerVersionLabel = new QLabel(headerWidget);
        headerVersionLabel->setObjectName(QString::fromUtf8("headerVersionLabel"));

        titleBox->addWidget(headerVersionLabel);


        leftBox->addLayout(titleBox);

        leftBoxSpacer = new QSpacerItem(12, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        leftBox->addItem(leftBoxSpacer);

        adminBadgeLabel = new QLabel(headerWidget);
        adminBadgeLabel->setObjectName(QString::fromUtf8("adminBadgeLabel"));

        leftBox->addWidget(adminBadgeLabel);


        headerLayout->addLayout(leftBox);

        headerStretch = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        headerLayout->addItem(headerStretch);

        infoBox = new QHBoxLayout();
        infoBox->setSpacing(24);
        infoBox->setObjectName(QString::fromUtf8("infoBox"));
        cpuLabel = new QVBoxLayout();
        cpuLabel->setSpacing(0);
        cpuLabel->setObjectName(QString::fromUtf8("cpuLabel"));
        cpuLoadTitleLabel = new QLabel(headerWidget);
        cpuLoadTitleLabel->setObjectName(QString::fromUtf8("cpuLoadTitleLabel"));

        cpuLabel->addWidget(cpuLoadTitleLabel);

        cpuLoadValueLabel = new QLabel(headerWidget);
        cpuLoadValueLabel->setObjectName(QString::fromUtf8("cpuLoadValueLabel"));

        cpuLabel->addWidget(cpuLoadValueLabel);


        infoBox->addLayout(cpuLabel);

        ramLabelBox = new QVBoxLayout();
        ramLabelBox->setSpacing(0);
        ramLabelBox->setObjectName(QString::fromUtf8("ramLabelBox"));
        ramTitleLabel = new QLabel(headerWidget);
        ramTitleLabel->setObjectName(QString::fromUtf8("ramTitleLabel"));

        ramLabelBox->addWidget(ramTitleLabel);

        ramValueLabel = new QLabel(headerWidget);
        ramValueLabel->setObjectName(QString::fromUtf8("ramValueLabel"));

        ramLabelBox->addWidget(ramValueLabel);


        infoBox->addLayout(ramLabelBox);


        headerLayout->addLayout(infoBox);


        mainLayout->addWidget(headerWidget);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(1);
        processPanelWidget = new QWidget(splitter);
        processPanelWidget->setObjectName(QString::fromUtf8("processPanelWidget"));
        processPanelLayout = new QVBoxLayout(processPanelWidget);
        processPanelLayout->setSpacing(6);
        processPanelLayout->setContentsMargins(11, 11, 11, 11);
        processPanelLayout->setObjectName(QString::fromUtf8("processPanelLayout"));
        processPanelLayout->setContentsMargins(8, 8, 4, 8);
        toolbar = new QHBoxLayout();
        toolbar->setSpacing(6);
        toolbar->setObjectName(QString::fromUtf8("toolbar"));
        monitorTitleLabel = new QLabel(processPanelWidget);
        monitorTitleLabel->setObjectName(QString::fromUtf8("monitorTitleLabel"));

        toolbar->addWidget(monitorTitleLabel);

        processCountBadgeLabel = new QLabel(processPanelWidget);
        processCountBadgeLabel->setObjectName(QString::fromUtf8("processCountBadgeLabel"));

        toolbar->addWidget(processCountBadgeLabel);

        toolbarSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        toolbar->addItem(toolbarSpacer);

        refreshButton = new QPushButton(processPanelWidget);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));

        toolbar->addWidget(refreshButton);

        speedButton = new QPushButton(processPanelWidget);
        speedButton->setObjectName(QString::fromUtf8("speedButton"));

        toolbar->addWidget(speedButton);


        processPanelLayout->addLayout(toolbar);

        typeitem = new QHBoxLayout();
        typeitem->setSpacing(6);
        typeitem->setObjectName(QString::fromUtf8("typeitem"));
        filterTypeLabel = new QLabel(processPanelWidget);
        filterTypeLabel->setObjectName(QString::fromUtf8("filterTypeLabel"));

        typeitem->addWidget(filterTypeLabel);

        typeitemSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        typeitem->addItem(typeitemSpacer);

        filterTypeComboBox = new QComboBox(processPanelWidget);
        filterTypeComboBox->setObjectName(QString::fromUtf8("filterTypeComboBox"));

        typeitem->addWidget(filterTypeComboBox);

        typeConfigButton = new QPushButton(processPanelWidget);
        typeConfigButton->setObjectName(QString::fromUtf8("typeConfigButton"));

        typeitem->addWidget(typeConfigButton);


        processPanelLayout->addLayout(typeitem);

        selectAllCheckBox = new QCheckBox(processPanelWidget);
        selectAllCheckBox->setObjectName(QString::fromUtf8("selectAllCheckBox"));

        processPanelLayout->addWidget(selectAllCheckBox);

        processTable = new QTableWidget(processPanelWidget);
        processTable->setObjectName(QString::fromUtf8("processTable"));
        processTable->setColumnCount(6);
        processTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        processTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        processTable->setShowGrid(false);
        processTable->setAlternatingRowColors(true);
        processTable->horizontalHeader()->setVisible(true);
        processTable->verticalHeader()->setVisible(false);

        processPanelLayout->addWidget(processTable);

        splitter->addWidget(processPanelWidget);
        controlPanelWidget = new QWidget(splitter);
        controlPanelWidget->setObjectName(QString::fromUtf8("controlPanelWidget"));
        controlPanelLayout = new QVBoxLayout(controlPanelWidget);
        controlPanelLayout->setSpacing(8);
        controlPanelLayout->setContentsMargins(11, 11, 11, 11);
        controlPanelLayout->setObjectName(QString::fromUtf8("controlPanelLayout"));
        controlPanelLayout->setContentsMargins(4, 8, 8, 8);
        searchGroupBox = new QGroupBox(controlPanelWidget);
        searchGroupBox->setObjectName(QString::fromUtf8("searchGroupBox"));
        searchLayout = new QVBoxLayout(searchGroupBox);
        searchLayout->setSpacing(6);
        searchLayout->setContentsMargins(11, 11, 11, 11);
        searchLayout->setObjectName(QString::fromUtf8("searchLayout"));
        searchLineEdit = new QLineEdit(searchGroupBox);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setClearButtonEnabled(true);

        searchLayout->addWidget(searchLineEdit);


        controlPanelLayout->addWidget(searchGroupBox);

        priorityGroupBox = new QGroupBox(controlPanelWidget);
        priorityGroupBox->setObjectName(QString::fromUtf8("priorityGroupBox"));
        priorityLayout = new QVBoxLayout(priorityGroupBox);
        priorityLayout->setSpacing(6);
        priorityLayout->setContentsMargins(11, 11, 11, 11);
        priorityLayout->setObjectName(QString::fromUtf8("priorityLayout"));
        realtimeRadio = new QRadioButton(priorityGroupBox);
        realtimeRadio->setObjectName(QString::fromUtf8("realtimeRadio"));

        priorityLayout->addWidget(realtimeRadio);

        highRadio = new QRadioButton(priorityGroupBox);
        highRadio->setObjectName(QString::fromUtf8("highRadio"));

        priorityLayout->addWidget(highRadio);

        aboveNormalRadio = new QRadioButton(priorityGroupBox);
        aboveNormalRadio->setObjectName(QString::fromUtf8("aboveNormalRadio"));

        priorityLayout->addWidget(aboveNormalRadio);

        normalRadio = new QRadioButton(priorityGroupBox);
        normalRadio->setObjectName(QString::fromUtf8("normalRadio"));
        normalRadio->setChecked(true);

        priorityLayout->addWidget(normalRadio);

        belowNormalRadio = new QRadioButton(priorityGroupBox);
        belowNormalRadio->setObjectName(QString::fromUtf8("belowNormalRadio"));

        priorityLayout->addWidget(belowNormalRadio);

        idleRadio = new QRadioButton(priorityGroupBox);
        idleRadio->setObjectName(QString::fromUtf8("idleRadio"));

        priorityLayout->addWidget(idleRadio);


        controlPanelLayout->addWidget(priorityGroupBox);

        affinityGroupBox = new QGroupBox(controlPanelWidget);
        affinityGroupBox->setObjectName(QString::fromUtf8("affinityGroupBox"));
        affinityLayout = new QVBoxLayout(affinityGroupBox);
        affinityLayout->setSpacing(6);
        affinityLayout->setContentsMargins(11, 11, 11, 11);
        affinityLayout->setObjectName(QString::fromUtf8("affinityLayout"));
        quickRow = new QHBoxLayout();
        quickRow->setSpacing(6);
        quickRow->setObjectName(QString::fromUtf8("quickRow"));
        selectAllCoresButton = new QPushButton(affinityGroupBox);
        selectAllCoresButton->setObjectName(QString::fromUtf8("selectAllCoresButton"));

        quickRow->addWidget(selectAllCoresButton);

        selectPhysicalCoresButton = new QPushButton(affinityGroupBox);
        selectPhysicalCoresButton->setObjectName(QString::fromUtf8("selectPhysicalCoresButton"));

        quickRow->addWidget(selectPhysicalCoresButton);

        clearCoresButton = new QPushButton(affinityGroupBox);
        clearCoresButton->setObjectName(QString::fromUtf8("clearCoresButton"));

        quickRow->addWidget(clearCoresButton);


        affinityLayout->addLayout(quickRow);


        controlPanelLayout->addWidget(affinityGroupBox);

        applyButton = new QPushButton(controlPanelWidget);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));
        applyButton->setEnabled(false);

        controlPanelLayout->addWidget(applyButton);

        controlPanelSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        controlPanelLayout->addItem(controlPanelSpacer);

        splitter->addWidget(controlPanelWidget);

        mainLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBarLabel = new QLabel(statusBar);
        statusBarLabel->setObjectName(QString::fromUtf8("statusBarLabel"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ProcessWarden v1.2.4", nullptr));
        headerWidget->setObjectName(QCoreApplication::translate("MainWindow", "header", nullptr));
        headerIconLabel->setObjectName(QCoreApplication::translate("MainWindow", "headerIcon", nullptr));
        headerIconLabel->setText(QCoreApplication::translate("MainWindow", "\356\200\200", nullptr));
        headerTitleLabel->setObjectName(QCoreApplication::translate("MainWindow", "headerTitle", nullptr));
        headerTitleLabel->setText(QCoreApplication::translate("MainWindow", "ProcessWarden", nullptr));
        headerVersionLabel->setObjectName(QCoreApplication::translate("MainWindow", "headerVersion", nullptr));
        headerVersionLabel->setText(QCoreApplication::translate("MainWindow", "v1.2.4", nullptr));
        adminBadgeLabel->setObjectName(QCoreApplication::translate("MainWindow", "adminBadgeOk", nullptr));
        adminBadgeLabel->setText(QCoreApplication::translate("MainWindow", "\342\227\217  Administrator Elevated", nullptr));
        cpuLoadTitleLabel->setObjectName(QCoreApplication::translate("MainWindow", "sysTitle", nullptr));
        cpuLoadTitleLabel->setText(QCoreApplication::translate("MainWindow", "System Load", nullptr));
        cpuLoadValueLabel->setObjectName(QCoreApplication::translate("MainWindow", "sysValue", nullptr));
        cpuLoadValueLabel->setText(QCoreApplication::translate("MainWindow", "-- %", nullptr));
        ramTitleLabel->setObjectName(QCoreApplication::translate("MainWindow", "sysTitle", nullptr));
        ramTitleLabel->setText(QCoreApplication::translate("MainWindow", "RAM Utilization", nullptr));
        ramValueLabel->setObjectName(QCoreApplication::translate("MainWindow", "sysValue", nullptr));
        ramValueLabel->setText(QCoreApplication::translate("MainWindow", "-- / -- GB", nullptr));
        processPanelWidget->setObjectName(QCoreApplication::translate("MainWindow", "panel", nullptr));
        monitorTitleLabel->setObjectName(QCoreApplication::translate("MainWindow", "sectionTitle", nullptr));
        monitorTitleLabel->setText(QCoreApplication::translate("MainWindow", "Process Monitor", nullptr));
        processCountBadgeLabel->setObjectName(QCoreApplication::translate("MainWindow", "badge", nullptr));
        processCountBadgeLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        refreshButton->setObjectName(QCoreApplication::translate("MainWindow", "smallBtn", nullptr));
        refreshButton->setText(QCoreApplication::translate("MainWindow", "\342\206\273  Refresh", nullptr));
        speedButton->setObjectName(QCoreApplication::translate("MainWindow", "smallBtn", nullptr));
        speedButton->setText(QCoreApplication::translate("MainWindow", "Refresh (3s)", nullptr));
        filterTypeLabel->setObjectName(QCoreApplication::translate("MainWindow", "sectionTitle", nullptr));
        filterTypeLabel->setText(QCoreApplication::translate("MainWindow", "Process Type", nullptr));
        typeConfigButton->setObjectName(QCoreApplication::translate("MainWindow", "smallBtn", nullptr));
        typeConfigButton->setText(QCoreApplication::translate("MainWindow", "Type Configuration", nullptr));
        selectAllCheckBox->setText(QString());
        controlPanelWidget->setObjectName(QCoreApplication::translate("MainWindow", "controlPanel", nullptr));
        searchGroupBox->setObjectName(QCoreApplication::translate("MainWindow", "ctrlGroup", nullptr));
        searchGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Search & Filter", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Name or PID...", nullptr));
        priorityGroupBox->setObjectName(QCoreApplication::translate("MainWindow", "ctrlGroup", nullptr));
        priorityGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Priority Class", nullptr));
        realtimeRadio->setObjectName(QCoreApplication::translate("MainWindow", "priRadio", nullptr));
        realtimeRadio->setText(QCoreApplication::translate("MainWindow", "Realtime", nullptr));
#if QT_CONFIG(tooltip)
        realtimeRadio->setToolTip(QCoreApplication::translate("MainWindow", "Reserved for critical sub-systems", nullptr));
#endif // QT_CONFIG(tooltip)
        highRadio->setObjectName(QCoreApplication::translate("MainWindow", "priRadio", nullptr));
        highRadio->setText(QCoreApplication::translate("MainWindow", "High", nullptr));
        aboveNormalRadio->setObjectName(QCoreApplication::translate("MainWindow", "priRadio", nullptr));
        aboveNormalRadio->setText(QCoreApplication::translate("MainWindow", "Above Normal", nullptr));
        normalRadio->setObjectName(QCoreApplication::translate("MainWindow", "priRadio", nullptr));
        normalRadio->setText(QCoreApplication::translate("MainWindow", "Normal", nullptr));
        belowNormalRadio->setObjectName(QCoreApplication::translate("MainWindow", "priRadio", nullptr));
        belowNormalRadio->setText(QCoreApplication::translate("MainWindow", "Below Normal", nullptr));
        idleRadio->setObjectName(QCoreApplication::translate("MainWindow", "priRadio", nullptr));
        idleRadio->setText(QCoreApplication::translate("MainWindow", "Idle", nullptr));
        affinityGroupBox->setObjectName(QCoreApplication::translate("MainWindow", "ctrlGroup", nullptr));
        affinityGroupBox->setTitle(QCoreApplication::translate("MainWindow", "CPU Affinity", nullptr));
        selectAllCoresButton->setObjectName(QCoreApplication::translate("MainWindow", "smallBtn", nullptr));
        selectAllCoresButton->setText(QCoreApplication::translate("MainWindow", "All Cores", nullptr));
        selectPhysicalCoresButton->setObjectName(QCoreApplication::translate("MainWindow", "smallBtn", nullptr));
        selectPhysicalCoresButton->setText(QCoreApplication::translate("MainWindow", "Physical Only", nullptr));
        clearCoresButton->setObjectName(QCoreApplication::translate("MainWindow", "smallBtn", nullptr));
        clearCoresButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        applyButton->setObjectName(QCoreApplication::translate("MainWindow", "applyBtn", nullptr));
        applyButton->setText(QCoreApplication::translate("MainWindow", "Apply to 0 Selected  \342\206\222", nullptr));
        statusBarLabel->setObjectName(QCoreApplication::translate("MainWindow", "statusLabel", nullptr));
        statusBarLabel->setText(QCoreApplication::translate("MainWindow", "  \342\227\217  System Ready", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
