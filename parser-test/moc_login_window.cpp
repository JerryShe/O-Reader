/****************************************************************************
** Meta object code from reading C++ file 'login_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "login_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LoginWindow_t {
    QByteArrayData data[15];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoginWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoginWindow_t qt_meta_stringdata_LoginWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "LoginWindow"
QT_MOC_LITERAL(1, 12, 22), // "on_exit_button_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 27), // "on_full_size_button_clicked"
QT_MOC_LITERAL(4, 64, 21), // "on_min_button_clicked"
QT_MOC_LITERAL(5, 86, 16), // "on_login_clicked"
QT_MOC_LITERAL(6, 103, 19), // "on_Recovery_clicked"
QT_MOC_LITERAL(7, 123, 23), // "on_Registration_clicked"
QT_MOC_LITERAL(8, 147, 14), // "backToMainPage"
QT_MOC_LITERAL(9, 162, 8), // "setStyle"
QT_MOC_LITERAL(10, 171, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(11, 186, 12), // "QMouseEvent*"
QT_MOC_LITERAL(12, 199, 1), // "e"
QT_MOC_LITERAL(13, 201, 15), // "mousePressEvent"
QT_MOC_LITERAL(14, 217, 17) // "mouseReleaseEvent"

    },
    "LoginWindow\0on_exit_button_clicked\0\0"
    "on_full_size_button_clicked\0"
    "on_min_button_clicked\0on_login_clicked\0"
    "on_Recovery_clicked\0on_Registration_clicked\0"
    "backToMainPage\0setStyle\0mouseMoveEvent\0"
    "QMouseEvent*\0e\0mousePressEvent\0"
    "mouseReleaseEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    1,   77,    2, 0x08 /* Private */,
      13,    1,   80,    2, 0x08 /* Private */,
      14,    1,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void LoginWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LoginWindow *_t = static_cast<LoginWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_exit_button_clicked(); break;
        case 1: _t->on_full_size_button_clicked(); break;
        case 2: _t->on_min_button_clicked(); break;
        case 3: _t->on_login_clicked(); break;
        case 4: _t->on_Recovery_clicked(); break;
        case 5: _t->on_Registration_clicked(); break;
        case 6: _t->backToMainPage(); break;
        case 7: _t->setStyle(); break;
        case 8: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 9: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 10: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject LoginWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LoginWindow.data,
      qt_meta_data_LoginWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LoginWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LoginWindow.stringdata0))
        return static_cast<void*>(const_cast< LoginWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LoginWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
