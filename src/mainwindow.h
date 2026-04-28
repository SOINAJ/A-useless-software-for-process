#pragma once

#include <QMainWindow>
#include <QButtonGroup>
#include <QCheckBox>
#include <QTimer>
#include <QVector>
#include <QSet>
#include <QTableWidgetItem>

#include "processinfo.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void refreshProcessList();
    void onSearchChanged(const QString& text);
    void onSelectAllToggled(bool checked);
    void onProcessChecked(QTableWidgetItem* item);
    void onPriorityChanged();
    void onAffinityToggled();
    void onSelectAllCores();
    void onSelectPhysicalCores();
    void onClearCores();
    void onApply();
    void onFilterTypeChanged(int index);

private:
    void setupDynamicUi();
    void applyStylesheet();

    void populateTable();
    int affinityMaskFromUi() const;
    void loadProcessItems();

    Ui::MainWindow* ui = nullptr;

    // Data
    QVector<ProcessInfo> m_allProcesses;
    QSet<DWORD> m_selectedPids;
    int m_logicalCores = 8;
    int m_physicalCores = 4;

    // Runtime-only (not representable in .ui)
    QButtonGroup* m_priorityGroup = nullptr;
    QVector<QCheckBox*> m_affinityChecks;

    // Timer
    QTimer* m_refreshTimer = nullptr;
    int m_refreshMs = 3000;

    //processes map
    QMap<QString, QStringList> allProcessData;
};
