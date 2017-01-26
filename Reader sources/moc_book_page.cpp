/****************************************************************************
** Meta object code from reading C++ file 'book_page.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "book_page.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'book_page.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BookPage_t {
    QByteArrayData data[7];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BookPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BookPage_t qt_meta_stringdata_BookPage = {
    {
QT_MOC_LITERAL(0, 0, 8), // "BookPage"
QT_MOC_LITERAL(1, 9, 12), // "startReading"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "index"
QT_MOC_LITERAL(4, 29, 10), // "deleteBook"
QT_MOC_LITERAL(5, 40, 23), // "on_startReading_clicked"
QT_MOC_LITERAL(6, 64, 21) // "on_deleteBook_clicked"

    },
    "BookPage\0startReading\0\0index\0deleteBook\0"
    "on_startReading_clicked\0on_deleteBook_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BookPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   40,    2, 0x08 /* Private */,
       6,    0,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BookPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BookPage *_t = static_cast<BookPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startReading((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->deleteBook((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_startReading_clicked(); break;
        case 3: _t->on_deleteBook_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BookPage::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BookPage::startReading)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BookPage::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BookPage::deleteBook)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject BookPage::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BookPage.data,
      qt_meta_data_BookPage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BookPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BookPage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BookPage.stringdata0))
        return static_cast<void*>(const_cast< BookPage*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BookPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
void BookPage::startReading(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BookPage::deleteBook(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
