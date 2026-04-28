#include "processmanager.h"

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <sddl.h>

bool ProcessManager::isRunAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = nullptr;
    SID_IDENTIFIER_AUTHORITY ntAuth = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&ntAuth, 2, SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        CheckTokenMembership(nullptr, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }
    return isAdmin != FALSE;
}

QVector<ProcessInfo> ProcessManager::enumerateProcesses() {
    QVector<ProcessInfo> list;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE)
        return list;

    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(pe);

    if (Process32FirstW(hSnap, &pe)) {
        do {
            ProcessInfo info;
            info.pid = pe.th32ProcessID;
            info.name = QString::fromWCharArray(pe.szExeFile);

            // PIDs 0 and 4 are system-critical
            info.isSystem = (info.pid == 0 || info.pid == 4);

            HANDLE hProc = OpenProcess(
                PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                FALSE, info.pid);

            if (hProc) {
                // Priority
                info.priority = GetPriorityClass(hProc);

                // Affinity
                DWORD_PTR procAffinity = 0, sysAffinity = 0;
                if (GetProcessAffinityMask(hProc, &procAffinity, &sysAffinity)) {
                    info.affinity = maskToCores(procAffinity);
                }

                // Memory
                PROCESS_MEMORY_COUNTERS_EX pmc;
                if (GetProcessMemoryInfo(hProc,
                        reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc),
                        sizeof(pmc))) {
                    info.memoryMB = pmc.WorkingSetSize / (1024.0 * 1024.0);
                }

                CloseHandle(hProc);
            } else {
                info.priority = NORMAL_PRIORITY_CLASS;
            }

            list.append(info);
        } while (Process32NextW(hSnap, &pe));
    }

    CloseHandle(hSnap);
    return list;
}

static DWORD s_lastError = 0;

static HANDLE openProcessForWrite(DWORD pid) {
    // Strategy: try from least to most privilege, stopping at first success.
    // Protected processes (PPL) reject PROCESS_VM_READ + PROCESS_QUERY_INFORMATION
    // but often accept PROCESS_QUERY_LIMITED_INFORMATION.

    HANDLE h = OpenProcess(PROCESS_SET_INFORMATION, FALSE, pid);
    if (h) return h;

    h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_SET_INFORMATION,
                    FALSE, pid);
    if (h) return h;

    h = OpenProcess(PROCESS_SET_INFORMATION | PROCESS_QUERY_INFORMATION |
                    PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION,
                    FALSE, pid);
    if (h) return h;

    h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!h) s_lastError = GetLastError();
    return h;
}

bool ProcessManager::enableDebugPrivilege() {
    HANDLE hToken = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(),
            TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return false;

    TOKEN_PRIVILEGES tp;
    LUID luid;
    if (!LookupPrivilegeValueW(nullptr, L"SeDebugPrivilege", &luid)) {
        CloseHandle(hToken);
        return false;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), nullptr, nullptr);
    // AdjustTokenPrivileges returns TRUE even when the privilege wasn't assigned
    DWORD err = GetLastError();
    CloseHandle(hToken);
    return err == ERROR_SUCCESS;
}

bool ProcessManager::setProcessPriority(DWORD pid, DWORD priorityClass) {
    HANDLE hProc = openProcessForWrite(pid);
    if (!hProc) return false;
    BOOL ok = SetPriorityClass(hProc, priorityClass);
    if (!ok) s_lastError = GetLastError();
    CloseHandle(hProc);
    return ok != FALSE;
}

bool ProcessManager::setProcessAffinity(DWORD pid, const QVector<int>& cores) {
    HANDLE hProc = openProcessForWrite(pid);
    if (!hProc) return false;
    DWORD_PTR mask = coresToMask(cores);
    BOOL ok = SetProcessAffinityMask(hProc, mask);
    if (!ok) s_lastError = GetLastError();
    CloseHandle(hProc);
    return ok != FALSE;
}

QString ProcessManager::lastErrorString() {
    if (s_lastError == 0) return QStringLiteral("Unknown error");

    LPWSTR buf = nullptr;
    DWORD len = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, s_lastError, 0, reinterpret_cast<LPWSTR>(&buf), 0, nullptr);

    QString result;
    if (buf && len > 0) {
        result = QString::fromWCharArray(buf, len).trimmed();
        result += QStringLiteral(" (code %1)").arg(s_lastError);
        LocalFree(buf);
    } else {
        result = QStringLiteral("Error code %1").arg(s_lastError);
    }

    // Reset
    s_lastError = 0;
    return result;
}

int ProcessManager::logicalProcessorCount() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwNumberOfProcessors;
}

int ProcessManager::physicalCoreCount() {
    DWORD len = 0;
    GetLogicalProcessorInformation(nullptr, &len);
    if (len == 0) return logicalProcessorCount();

    QVector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> buf(
        len / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));
    if (!GetLogicalProcessorInformation(buf.data(), &len))
        return logicalProcessorCount();

    int count = 0;
    for (const auto& info : buf) {
        if (info.Relationship == RelationProcessorCore)
            ++count;
    }
    return count > 0 ? count : logicalProcessorCount();
}

QPair<double, double> ProcessManager::systemMemory() {
    MEMORYSTATUSEX ms;
    ms.dwLength = sizeof(ms);
    GlobalMemoryStatusEx(&ms);
    double total = ms.ullTotalPhys / (1024.0 * 1024.0 * 1024.0);
    double used = (ms.ullTotalPhys - ms.ullAvailPhys) / (1024.0 * 1024.0 * 1024.0);
    return { total, used };
}

DWORD_PTR ProcessManager::coresToMask(const QVector<int>& cores) {
    DWORD_PTR mask = 0;
    for (int c : cores)
        mask |= (static_cast<DWORD_PTR>(1) << c);
    return mask;
}

QVector<int> ProcessManager::maskToCores(DWORD_PTR mask) {
    QVector<int> cores;
    for (int i = 0; i < static_cast<int>(sizeof(DWORD_PTR) * 8); ++i) {
        if (mask & (static_cast<DWORD_PTR>(1) << i))
            cores.append(i);
    }
    return cores;
}
