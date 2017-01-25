/****************************************************************************
** Meta object code from reading C++ file 'settings_layout.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "settings_layout.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settings_layout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_settingslayout_t {
    QByteArrayData data[11];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_settingslayout_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_settingslayout_t qt_meta_stringdata_settingslayout = {
    {
QT_MOC_LITERAL(0, 0, 14), // "settingslayout"
QT_MOC_LITERAL(1, 15, 14), // "settingsClosed"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 15), // "settingsChanged"
QT_MOC_LITERAL(4, 47, 11), // "showProfile"
QT_MOC_LITERAL(5, 59, 11), // "showProgram"
QT_MOC_LITERAL(6, 71, 10), // "showReader"
QT_MOC_LITERAL(7, 82, 13), // "addExitButton"
QT_MOC_LITERAL(8, 96, 17), // "updateSavebuttons"
QT_MOC_LITERAL(9, 114, 4), // "type"
QT_MOC_LITERAL(10, 119, 19) // "exit_button_clicked"

    },
    "settingslayout\0settingsClosed\0\0"
    "settingsChanged\0showProfile\0showProgram\0"
    "showReader\0addExitButton\0updateSavebuttons\0"
    "type\0exit_button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_settingslayout[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    1,   60,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,

       0        // eod
};

void settingslayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        settingslayout *_t = static_cast<settingslayout *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->settingsClosed(); break;
        case 1: _t->settingsChanged(); break;
        case 2: _t->showProfile(); break;
        case 3: _t->showProgram(); break;
        case 4: _t->showReader(); break;
        case 5: _t->addExitButton(); break;
        case 6: _t->updateSavebuttons((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->exit_button_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (settingslayout::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&settingslayout::settingsClosed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (settingslayout::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&settingslayout::settingsChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject settingslayout::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_settingslayout.data,
      qt_meta_data_settingslayout,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *settingslayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *settingslayout::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_settingslayout.stringdata0))
        return static_cast<void*>(const_cast< settingslayout*>(this));
    return QWidget::qt_metacast(_clname);
}

int settingslayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void settingslayout::settingsClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void settingslayout::settingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
