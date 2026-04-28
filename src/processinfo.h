#pragma once

#include <windows.h>
#include <QString>
#include <QVector>

enum class PriorityClass {
    REALTIME = REALTIME_PRIORITY_CLASS,
    HIGH = HIGH_PRIORITY_CLASS,
    ABOVE_NORMAL = ABOVE_NORMAL_PRIORITY_CLASS,
    NORMAL = NORMAL_PRIORITY_CLASS,
    BELOW_NORMAL = BELOW_NORMAL_PRIORITY_CLASS,
    IDLE = IDLE_PRIORITY_CLASS
};

struct ProcessInfo {
    DWORD pid = 0;
    QString name;
    DWORD priority = NORMAL_PRIORITY_CLASS;
    QVector<int> affinity;
    double memoryMB = 0.0;
    bool isSystem = false;
};

inline PriorityClass priorityFromDword(DWORD p) {
    switch (p) {
        case REALTIME_PRIORITY_CLASS:   return PriorityClass::REALTIME;
        case HIGH_PRIORITY_CLASS:       return PriorityClass::HIGH;
        case ABOVE_NORMAL_PRIORITY_CLASS: return PriorityClass::ABOVE_NORMAL;
        case BELOW_NORMAL_PRIORITY_CLASS: return PriorityClass::BELOW_NORMAL;
        case IDLE_PRIORITY_CLASS:       return PriorityClass::IDLE;
        default:                        return PriorityClass::NORMAL;
    }
}

inline QString priorityToString(DWORD p) {
    switch (p) {
        case REALTIME_PRIORITY_CLASS:   return QStringLiteral("Realtime");
        case HIGH_PRIORITY_CLASS:       return QStringLiteral("High");
        case ABOVE_NORMAL_PRIORITY_CLASS: return QStringLiteral("Above Normal");
        case BELOW_NORMAL_PRIORITY_CLASS: return QStringLiteral("Below Normal");
        case IDLE_PRIORITY_CLASS:       return QStringLiteral("Idle");
        default:                        return QStringLiteral("Normal");
    }
}

inline QString priorityToString(PriorityClass p) {
    return priorityToString(static_cast<DWORD>(p));
}
