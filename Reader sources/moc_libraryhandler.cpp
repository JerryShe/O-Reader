/****************************************************************************
** Meta object code from reading C++ file 'libraryhandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "libraryhandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'libraryhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LibraryHandler_t {
    QByteArrayData data[22];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LibraryHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LibraryHandler_t qt_meta_stringdata_LibraryHandler = {
    {
QT_MOC_LITERAL(0, 0, 14), // "LibraryHandler"
QT_MOC_LITERAL(1, 15, 8), // "AddBooks"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "fileList"
QT_MOC_LITERAL(4, 34, 9), // "AddFolder"
QT_MOC_LITERAL(5, 44, 4), // "path"
QT_MOC_LITERAL(6, 49, 10), // "deleteBook"
QT_MOC_LITERAL(7, 60, 5), // "index"
QT_MOC_LITERAL(8, 66, 11), // "deleteBooks"
QT_MOC_LITERAL(9, 78, 12), // "QVector<int>"
QT_MOC_LITERAL(10, 91, 19), // "deletedItemsIndexes"
QT_MOC_LITERAL(11, 111, 12), // "openNewBooks"
QT_MOC_LITERAL(12, 124, 10), // "GenresMap*"
QT_MOC_LITERAL(13, 135, 4), // "Gmap"
QT_MOC_LITERAL(14, 140, 11), // "getFileTipe"
QT_MOC_LITERAL(15, 152, 8), // "fileName"
QT_MOC_LITERAL(16, 161, 9), // "findBooks"
QT_MOC_LITERAL(17, 171, 3), // "key"
QT_MOC_LITERAL(18, 175, 4), // "mode"
QT_MOC_LITERAL(19, 180, 12), // "loadBookList"
QT_MOC_LITERAL(20, 193, 12), // "saveBookList"
QT_MOC_LITERAL(21, 206, 9) // "sortBooks"

    },
    "LibraryHandler\0AddBooks\0\0fileList\0"
    "AddFolder\0path\0deleteBook\0index\0"
    "deleteBooks\0QVector<int>\0deletedItemsIndexes\0"
    "openNewBooks\0GenresMap*\0Gmap\0getFileTipe\0"
    "fileName\0findBooks\0key\0mode\0loadBookList\0"
    "saveBookList\0sortBooks"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LibraryHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       6,    1,   70,    2, 0x0a /* Public */,
       8,    1,   73,    2, 0x0a /* Public */,
      11,    2,   76,    2, 0x0a /* Public */,
      14,    1,   81,    2, 0x0a /* Public */,
      16,    2,   84,    2, 0x0a /* Public */,
      19,    0,   89,    2, 0x0a /* Public */,
      20,    0,   90,    2, 0x0a /* Public */,
      21,    1,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 12,    3,   13,
    QMetaType::QString, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

void LibraryHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LibraryHandler *_t = static_cast<LibraryHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddBooks((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: _t->AddFolder((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->deleteBook((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->deleteBooks((*reinterpret_cast< QVector<int>(*)>(_a[1]))); break;
        case 4: _t->openNewBooks((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< GenresMap*(*)>(_a[2]))); break;
        case 5: { QString _r = _t->getFileTipe((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: _t->findBooks((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->loadBookList(); break;
        case 8: _t->saveBookList(); break;
        case 9: _t->sortBooks((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    }
}

const QMetaObject LibraryHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LibraryHandler.data,
      qt_meta_data_LibraryHandler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LibraryHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LibraryHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LibraryHandler.stringdata0))
        return static_cast<void*>(const_cast< LibraryHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int LibraryHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
