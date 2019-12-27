/****************************************************************************
** Meta object code from reading C++ file 'Client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ImClient/Client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[17];
    char stringdata0[291];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 19), // "UM_GET_LOGON_RESULT"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 18), // "const LogonResult*"
QT_MOC_LITERAL(4, 47, 17), // "UM_GET_REG_RESULT"
QT_MOC_LITERAL(5, 65, 16), // "const RegResult*"
QT_MOC_LITERAL(6, 82, 25), // "UM_GET_ADD_FRIEND_REQUEST"
QT_MOC_LITERAL(7, 108, 23), // "const AddFriendRequest*"
QT_MOC_LITERAL(8, 132, 24), // "UM_GET_ADD_FRIEND_RESULT"
QT_MOC_LITERAL(9, 157, 22), // "const AddFriendResult*"
QT_MOC_LITERAL(10, 180, 11), // "UM_CHAT_S2C"
QT_MOC_LITERAL(11, 192, 15), // "const ChatInfo*"
QT_MOC_LITERAL(12, 208, 16), // "UM_FRIEND_LOGOFF"
QT_MOC_LITERAL(13, 225, 20), // "const LogoffRequest*"
QT_MOC_LITERAL(14, 246, 15), // "UM_FRIEND_LOGON"
QT_MOC_LITERAL(15, 262, 18), // "const FriendLogon*"
QT_MOC_LITERAL(16, 281, 9) // "onReceive"

    },
    "Client\0UM_GET_LOGON_RESULT\0\0"
    "const LogonResult*\0UM_GET_REG_RESULT\0"
    "const RegResult*\0UM_GET_ADD_FRIEND_REQUEST\0"
    "const AddFriendRequest*\0"
    "UM_GET_ADD_FRIEND_RESULT\0"
    "const AddFriendResult*\0UM_CHAT_S2C\0"
    "const ChatInfo*\0UM_FRIEND_LOGOFF\0"
    "const LogoffRequest*\0UM_FRIEND_LOGON\0"
    "const FriendLogon*\0onReceive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    1,   60,    2, 0x06 /* Public */,
       8,    1,   63,    2, 0x06 /* Public */,
      10,    1,   66,    2, 0x06 /* Public */,
      12,    1,   69,    2, 0x06 /* Public */,
      14,    1,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, 0x80000000 | 15,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Client *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UM_GET_LOGON_RESULT((*reinterpret_cast< const LogonResult*(*)>(_a[1]))); break;
        case 1: _t->UM_GET_REG_RESULT((*reinterpret_cast< const RegResult*(*)>(_a[1]))); break;
        case 2: _t->UM_GET_ADD_FRIEND_REQUEST((*reinterpret_cast< const AddFriendRequest*(*)>(_a[1]))); break;
        case 3: _t->UM_GET_ADD_FRIEND_RESULT((*reinterpret_cast< const AddFriendResult*(*)>(_a[1]))); break;
        case 4: _t->UM_CHAT_S2C((*reinterpret_cast< const ChatInfo*(*)>(_a[1]))); break;
        case 5: _t->UM_FRIEND_LOGOFF((*reinterpret_cast< const LogoffRequest*(*)>(_a[1]))); break;
        case 6: _t->UM_FRIEND_LOGON((*reinterpret_cast< const FriendLogon*(*)>(_a[1]))); break;
        case 7: _t->onReceive(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Client::*_t)(const LogonResult * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::UM_GET_LOGON_RESULT)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const RegResult * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::UM_GET_REG_RESULT)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const AddFriendRequest * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::UM_GET_ADD_FRIEND_REQUEST)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const AddFriendResult * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::UM_GET_ADD_FRIEND_RESULT)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const ChatInfo * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::UM_CHAT_S2C)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const LogoffRequest * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::UM_FRIEND_LOGOFF)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const FriendLogon * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::UM_FRIEND_LOGON)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject Client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Client.data,
      qt_meta_data_Client,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata0))
        return static_cast<void*>(const_cast< Client*>(this));
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Client::UM_GET_LOGON_RESULT(const LogonResult * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Client::UM_GET_REG_RESULT(const RegResult * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Client::UM_GET_ADD_FRIEND_REQUEST(const AddFriendRequest * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Client::UM_GET_ADD_FRIEND_RESULT(const AddFriendResult * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Client::UM_CHAT_S2C(const ChatInfo * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Client::UM_FRIEND_LOGOFF(const LogoffRequest * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Client::UM_FRIEND_LOGON(const FriendLogon * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
