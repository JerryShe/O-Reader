/****************************************************************************
** Meta object code from reading C++ file 'settings_profilelayout.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "settings_profilelayout.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settings_profilelayout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Settings_ProfileLayout_t {
    QByteArrayData data[6];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Settings_ProfileLayout_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Settings_ProfileLayout_t qt_meta_stringdata_Settings_ProfileLayout = {
    {
QT_MOC_LITERAL(0, 0, 22), // "Settings_ProfileLayout"
QT_MOC_LITERAL(1, 23, 15), // "settingsChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 4), // "type"
QT_MOC_LITERAL(4, 45, 31), // "on_ChangePasswordButton_clicked"
QT_MOC_LITERAL(5, 77, 21) // "on_SaveButton_clicked"

    },
    "Settings_ProfileLayout\0settingsChanged\0"
    "\0type\0on_ChangePasswordButton_clicked\0"
    "on_SaveButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Settings_ProfileLayout[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Settings_ProfileLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Settings_ProfileLayout *_t = static_cast<Settings_ProfileLayout *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->settingsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_ChangePasswordButton_clicked(); break;
        case 2: _t->on_SaveButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Settings_ProfileLayout::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Settings_ProfileLayout::settingsChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Settings_ProfileLayout::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_Settings_ProfileLayout.data,
      qt_meta_data_Settings_ProfileLayout,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Settings_ProfileLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Settings_ProfileLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Settings_ProfileLayout.stringdata0))
        return static_cast<void*>(const_cast< Settings_ProfileLayout*>(this));
    return QFrame::qt_metacast(_clname);
}

int Settings_ProfileLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Settings_ProfileLayout::settingsChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
