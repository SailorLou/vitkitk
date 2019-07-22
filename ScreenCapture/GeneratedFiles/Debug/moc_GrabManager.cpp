/****************************************************************************
** Meta object code from reading C++ file 'GrabManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GrabManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GrabManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GrabManager_t {
    QByteArrayData data[6];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GrabManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GrabManager_t qt_meta_stringdata_GrabManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GrabManager"
QT_MOC_LITERAL(1, 12, 17), // "hideMainInterface"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "showMainInterface"
QT_MOC_LITERAL(4, 49, 11), // "newSnapshot"
QT_MOC_LITERAL(5, 61, 15) // "grabCurrentMode"

    },
    "GrabManager\0hideMainInterface\0\0"
    "showMainInterface\0newSnapshot\0"
    "grabCurrentMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GrabManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    1,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void GrabManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GrabManager *_t = static_cast<GrabManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hideMainInterface(); break;
        case 1: _t->showMainInterface(); break;
        case 2: _t->newSnapshot((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 3: _t->grabCurrentMode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (GrabManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GrabManager::hideMainInterface)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GrabManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GrabManager::showMainInterface)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GrabManager::*_t)(const QPixmap & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GrabManager::newSnapshot)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject GrabManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GrabManager.data,
      qt_meta_data_GrabManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GrabManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GrabManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GrabManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GrabManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GrabManager::hideMainInterface()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GrabManager::showMainInterface()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GrabManager::newSnapshot(const QPixmap & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
