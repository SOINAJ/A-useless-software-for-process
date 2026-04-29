/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "refreshProcessList"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 15), // "onSearchChanged"
QT_MOC_LITERAL(4, 47, 4), // "text"
QT_MOC_LITERAL(5, 52, 18), // "onSelectAllToggled"
QT_MOC_LITERAL(6, 71, 7), // "checked"
QT_MOC_LITERAL(7, 79, 16), // "onProcessChecked"
QT_MOC_LITERAL(8, 96, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(9, 114, 4), // "item"
QT_MOC_LITERAL(10, 119, 17), // "onPriorityChanged"
QT_MOC_LITERAL(11, 137, 17), // "onAffinityToggled"
QT_MOC_LITERAL(12, 155, 16), // "onSelectAllCores"
QT_MOC_LITERAL(13, 172, 21), // "onSelectPhysicalCores"
QT_MOC_LITERAL(14, 194, 12), // "onClearCores"
QT_MOC_LITERAL(15, 207, 7), // "onApply"
QT_MOC_LITERAL(16, 215, 19), // "onFilterTypeChanged"
QT_MOC_LITERAL(17, 235, 5), // "index"
QT_MOC_LITERAL(18, 241, 8) // "openType"

    },
    "MainWindow\0refreshProcessList\0\0"
    "onSearchChanged\0text\0onSelectAllToggled\0"
    "checked\0onProcessChecked\0QTableWidgetItem*\0"
    "item\0onPriorityChanged\0onAffinityToggled\0"
    "onSelectAllCores\0onSelectPhysicalCores\0"
    "onClearCores\0onApply\0onFilterTypeChanged\0"
    "index\0openType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       5,    1,   78,    2, 0x08 /* Private */,
       7,    1,   81,    2, 0x08 /* Private */,
      10,    0,   84,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    0,   89,    2, 0x08 /* Private */,
      16,    1,   90,    2, 0x08 /* Private */,
      18,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refreshProcessList(); break;
        case 1: _t->onSearchChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onSelectAllToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onProcessChecked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->onPriorityChanged(); break;
        case 5: _t->onAffinityToggled(); break;
        case 6: _t->onSelectAllCores(); break;
        case 7: _t->onSelectPhysicalCores(); break;
        case 8: _t->onClearCores(); break;
        case 9: _t->onApply(); break;
        case 10: _t->onFilterTypeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->openType(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
