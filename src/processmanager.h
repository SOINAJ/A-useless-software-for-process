#pragma once

#include "processinfo.h"
#include <QVector>
#include <QPair>

class ProcessManager {
public:
    static bool isRunAsAdmin();
    static bool enableDebugPrivilege();
    static QVector<ProcessInfo> enumerateProcesses();
    static bool setProcessPriority(DWORD pid, DWORD priorityClass);
    static bool setProcessAffinity(DWORD pid, const QVector<int>& cores);
    static int logicalProcessorCount();
    static int physicalCoreCount();
    static QPair<double, double> systemMemory();  // returns (totalGB, usedGB)
    static QString lastErrorString();

    static DWORD_PTR coresToMask(const QVector<int>& cores);

private:
    static QVector<int> maskToCores(DWORD_PTR mask);
};
