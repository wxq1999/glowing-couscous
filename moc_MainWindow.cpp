/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ImClient/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[440];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "on_buttonLogon_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 22), // "on_buttonReg_triggered"
QT_MOC_LITERAL(4, 60, 28), // "on_buttonAddFriend_triggered"
QT_MOC_LITERAL(5, 89, 24), // "on_buttonMChat_triggered"
QT_MOC_LITERAL(6, 114, 25), // "on_buttonLogoff_triggered"
QT_MOC_LITERAL(7, 140, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(8, 160, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(9, 177, 16), // "onGetLogonResult"
QT_MOC_LITERAL(10, 194, 18), // "const LogonResult*"
QT_MOC_LITERAL(11, 213, 14), // "onGetRegResult"
QT_MOC_LITERAL(12, 228, 16), // "const RegResult*"
QT_MOC_LITERAL(13, 245, 9), // "onChatC2S"
QT_MOC_LITERAL(14, 255, 15), // "const ChatInfo*"
QT_MOC_LITERAL(15, 271, 9), // "onChatS2C"
QT_MOC_LITERAL(16, 281, 21), // "onGetAddFriendRequest"
QT_MOC_LITERAL(17, 303, 23), // "const AddFriendRequest*"
QT_MOC_LITERAL(18, 327, 20), // "onGetAddFriendResult"
QT_MOC_LITERAL(19, 348, 22), // "const AddFriendResult*"
QT_MOC_LITERAL(20, 371, 14), // "onFriendLogoff"
QT_MOC_LITERAL(21, 386, 20), // "const LogoffRequest*"
QT_MOC_LITERAL(22, 407, 13), // "onFriendLogon"
QT_MOC_LITERAL(23, 421, 18) // "const FriendLogon*"

    },
    "MainWindow\0on_buttonLogon_triggered\0"
    "\0on_buttonReg_triggered\0"
    "on_buttonAddFriend_triggered\0"
    "on_buttonMChat_triggered\0"
    "on_buttonLogoff_triggered\0onItemDoubleClicked\0"
    "QListWidgetItem*\0onGetLogonResult\0"
    "const LogonResult*\0onGetRegResult\0"
    "const RegResult*\0onChatC2S\0const ChatInfo*\0"
    "onChatS2C\0onGetAddFriendRequest\0"
    "const AddFriendRequest*\0onGetAddFriendResult\0"
    "const AddFriendResult*\0onFriendLogoff\0"
    "const LogoffRequest*\0onFriendLogon\0"
    "const FriendLogon*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    1,   89,    2, 0x08 /* Private */,
       9,    1,   92,    2, 0x08 /* Private */,
      11,    1,   95,    2, 0x08 /* Private */,
      13,    1,   98,    2, 0x08 /* Private */,
      15,    1,  101,    2, 0x08 /* Private */,
      16,    1,  104,    2, 0x08 /* Private */,
      18,    1,  107,    2, 0x08 /* Private */,
      20,    1,  110,    2, 0x08 /* Private */,
      22,    1,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 19,    2,
    QMetaType::Void, 0x80000000 | 21,    2,
    QMetaType::Void, 0x80000000 | 23,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_buttonLogon_triggered(); break;
        case 1: _t->on_buttonReg_triggered(); break;
        case 2: _t->on_buttonAddFriend_triggered(); break;
        case 3: _t->on_buttonMChat_triggered(); break;
        case 4: _t->on_buttonLogoff_triggered(); break;
        case 5: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->onGetLogonResult((*reinterpret_cast< const LogonResult*(*)>(_a[1]))); break;
        case 7: _t->onGetRegResult((*reinterpret_cast< const RegResult*(*)>(_a[1]))); break;
        case 8: _t->onChatC2S((*reinterpret_cast< const ChatInfo*(*)>(_a[1]))); break;
        case 9: _t->onChatS2C((*reinterpret_cast< const ChatInfo*(*)>(_a[1]))); break;
        case 10: _t->onGetAddFriendRequest((*reinterpret_cast< const AddFriendRequest*(*)>(_a[1]))); break;
        case 11: _t->onGetAddFriendResult((*reinterpret_cast< const AddFriendResult*(*)>(_a[1]))); break;
        case 12: _t->onFriendLogoff((*reinterpret_cast< const LogoffRequest*(*)>(_a[1]))); break;
        case 13: _t->onFriendLogon((*reinterpret_cast< const FriendLogon*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
