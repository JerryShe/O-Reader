/****************************************************************************
** Meta object code from reading C++ file 'search_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "search_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'search_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SearchWindow_t {
    QByteArrayData data[14];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchWindow_t qt_meta_stringdata_SearchWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SearchWindow"
QT_MOC_LITERAL(1, 13, 11), // "startSearch"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "token"
QT_MOC_LITERAL(4, 32, 10), // "searchType"
QT_MOC_LITERAL(5, 43, 14), // "previousResult"
QT_MOC_LITERAL(6, 58, 10), // "nextResult"
QT_MOC_LITERAL(7, 69, 12), // "windowClosed"
QT_MOC_LITERAL(8, 82, 16), // "YepButtonClicked"
QT_MOC_LITERAL(9, 99, 17), // "NopeButtonClicked"
QT_MOC_LITERAL(10, 117, 17), // "exitButtonClicked"
QT_MOC_LITERAL(11, 135, 11), // "TextChanged"
QT_MOC_LITERAL(12, 147, 8), // "setStyle"
QT_MOC_LITERAL(13, 156, 5) // "style"

    },
    "SearchWindow\0startSearch\0\0token\0"
    "searchType\0previousResult\0nextResult\0"
    "windowClosed\0YepButtonClicked\0"
    "NopeButtonClicked\0exitButtonClicked\0"
    "TextChanged\0setStyle\0style"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    0,   64,    2, 0x06 /* Public */,
       6,    0,   65,    2, 0x06 /* Public */,
       7,    0,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   67,    2, 0x08 /* Private */,
       9,    0,   68,    2, 0x08 /* Private */,
      10,    0,   69,    2, 0x08 /* Private */,
      11,    0,   70,    2, 0x08 /* Private */,
      12,    1,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void SearchWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SearchWindow *_t = static_cast<SearchWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startSearch((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->previousResult(); break;
        case 2: _t->nextResult(); break;
        case 3: _t->windowClosed(); break;
        case 4: _t->YepButtonClicked(); break;
        case 5: _t->NopeButtonClicked(); break;
        case 6: _t->exitButtonClicked(); break;
        case 7: _t->TextChanged(); break;
        case 8: _t->setStyle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SearchWindow::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SearchWindow::startSearch)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SearchWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SearchWindow::previousResult)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SearchWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SearchWindow::nextResult)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (SearchWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SearchWindow::windowClosed)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject SearchWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SearchWindow.data,
      qt_meta_data_SearchWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SearchWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SearchWindow.stringdata0))
        return static_cast<void*>(const_cast< SearchWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int SearchWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SearchWindow::startSearch(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SearchWindow::previousResult()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void SearchWindow::nextResult()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void SearchWindow::windowClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
