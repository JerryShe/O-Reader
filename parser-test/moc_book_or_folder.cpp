/****************************************************************************
** Meta object code from reading C++ file 'book_or_folder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "book_or_folder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'book_or_folder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BookOrFolder_t {
    QByteArrayData data[6];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BookOrFolder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BookOrFolder_t qt_meta_stringdata_BookOrFolder = {
    {
QT_MOC_LITERAL(0, 0, 12), // "BookOrFolder"
QT_MOC_LITERAL(1, 13, 13), // "AddBookSignal"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 15), // "AddFolderSignal"
QT_MOC_LITERAL(4, 44, 16), // "DeleteBookSignal"
QT_MOC_LITERAL(5, 61, 18) // "DeleteFolderSignal"

    },
    "BookOrFolder\0AddBookSignal\0\0AddFolderSignal\0"
    "DeleteBookSignal\0DeleteFolderSignal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BookOrFolder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BookOrFolder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BookOrFolder *_t = static_cast<BookOrFolder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddBookSignal(); break;
        case 1: _t->AddFolderSignal(); break;
        case 2: _t->DeleteBookSignal(); break;
        case 3: _t->DeleteFolderSignal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BookOrFolder::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BookOrFolder::AddBookSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BookOrFolder::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BookOrFolder::AddFolderSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (BookOrFolder::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BookOrFolder::DeleteBookSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (BookOrFolder::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BookOrFolder::DeleteFolderSignal)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject BookOrFolder::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BookOrFolder.data,
      qt_meta_data_BookOrFolder,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BookOrFolder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BookOrFolder::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BookOrFolder.stringdata0))
        return static_cast<void*>(const_cast< BookOrFolder*>(this));
    return QDialog::qt_metacast(_clname);
}

int BookOrFolder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void BookOrFolder::AddBookSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void BookOrFolder::AddFolderSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void BookOrFolder::DeleteBookSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void BookOrFolder::DeleteFolderSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
