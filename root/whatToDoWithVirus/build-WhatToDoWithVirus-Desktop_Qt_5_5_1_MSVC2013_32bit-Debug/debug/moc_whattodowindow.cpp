/****************************************************************************
** Meta object code from reading C++ file 'whattodowindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/whattodowindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'whattodowindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WhatToDoWindow_t {
    QByteArrayData data[6];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WhatToDoWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WhatToDoWindow_t qt_meta_stringdata_WhatToDoWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "WhatToDoWindow"
QT_MOC_LITERAL(1, 15, 7), // "signal1"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "delete_it"
QT_MOC_LITERAL(4, 34, 9), // "ignore_it"
QT_MOC_LITERAL(5, 44, 13) // "quarantine_it"

    },
    "WhatToDoWindow\0signal1\0\0delete_it\0"
    "ignore_it\0quarantine_it"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WhatToDoWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   37,    2, 0x0a /* Public */,
       4,    0,   38,    2, 0x0a /* Public */,
       5,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WhatToDoWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WhatToDoWindow *_t = static_cast<WhatToDoWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->delete_it(); break;
        case 2: _t->ignore_it(); break;
        case 3: _t->quarantine_it(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WhatToDoWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WhatToDoWindow::signal1)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject WhatToDoWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WhatToDoWindow.data,
      qt_meta_data_WhatToDoWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WhatToDoWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WhatToDoWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WhatToDoWindow.stringdata0))
        return static_cast<void*>(const_cast< WhatToDoWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int WhatToDoWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void WhatToDoWindow::signal1(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
