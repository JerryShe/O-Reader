/****************************************************************************
** Meta object code from reading C++ file 'reading_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../parser-test/reading_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reading_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ReadingWindow_t {
    QByteArrayData data[28];
    char stringdata0[458];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReadingWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReadingWindow_t qt_meta_stringdata_ReadingWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ReadingWindow"
QT_MOC_LITERAL(1, 14, 14), // "showMainWindow"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "windowWasResized"
QT_MOC_LITERAL(4, 47, 16), // "saveBookProgress"
QT_MOC_LITERAL(5, 64, 21), // "on_min_button_clicked"
QT_MOC_LITERAL(6, 86, 27), // "on_full_size_button_clicked"
QT_MOC_LITERAL(7, 114, 22), // "on_exit_button_clicked"
QT_MOC_LITERAL(8, 137, 21), // "on_MenuButton_clicked"
QT_MOC_LITERAL(9, 159, 22), // "ContentsButton_clicked"
QT_MOC_LITERAL(10, 182, 18), // "FindButton_Clicked"
QT_MOC_LITERAL(11, 201, 22), // "SettingsButton_Clicked"
QT_MOC_LITERAL(12, 224, 29), // "SynchronizationButton_Clicked"
QT_MOC_LITERAL(13, 254, 30), // "BackToMainWindowButton_Clicked"
QT_MOC_LITERAL(14, 285, 8), // "setStyle"
QT_MOC_LITERAL(15, 294, 12), // "currentStyle"
QT_MOC_LITERAL(16, 307, 11), // "StartSearch"
QT_MOC_LITERAL(17, 319, 3), // "key"
QT_MOC_LITERAL(18, 323, 4), // "type"
QT_MOC_LITERAL(19, 328, 14), // "NextSearchStep"
QT_MOC_LITERAL(20, 343, 14), // "PrevSearchStep"
QT_MOC_LITERAL(21, 358, 9), // "clockStep"
QT_MOC_LITERAL(22, 368, 14), // "updateProgress"
QT_MOC_LITERAL(23, 383, 18), // "reprintResizedText"
QT_MOC_LITERAL(24, 402, 18), // "reprintNewSettText"
QT_MOC_LITERAL(25, 421, 11), // "goToSection"
QT_MOC_LITERAL(26, 433, 12), // "sectionIndex"
QT_MOC_LITERAL(27, 446, 11) // "saveBookPos"

    },
    "ReadingWindow\0showMainWindow\0\0"
    "windowWasResized\0saveBookProgress\0"
    "on_min_button_clicked\0on_full_size_button_clicked\0"
    "on_exit_button_clicked\0on_MenuButton_clicked\0"
    "ContentsButton_clicked\0FindButton_Clicked\0"
    "SettingsButton_Clicked\0"
    "SynchronizationButton_Clicked\0"
    "BackToMainWindowButton_Clicked\0setStyle\0"
    "currentStyle\0StartSearch\0key\0type\0"
    "NextSearchStep\0PrevSearchStep\0clockStep\0"
    "updateProgress\0reprintResizedText\0"
    "reprintNewSettText\0goToSection\0"
    "sectionIndex\0saveBookPos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReadingWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x06 /* Public */,
       3,    0,  125,    2, 0x06 /* Public */,
       4,    0,  126,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  127,    2, 0x08 /* Private */,
       6,    0,  128,    2, 0x08 /* Private */,
       7,    0,  129,    2, 0x08 /* Private */,
       8,    0,  130,    2, 0x08 /* Private */,
       9,    0,  131,    2, 0x08 /* Private */,
      10,    0,  132,    2, 0x08 /* Private */,
      11,    0,  133,    2, 0x08 /* Private */,
      12,    0,  134,    2, 0x08 /* Private */,
      13,    0,  135,    2, 0x08 /* Private */,
      14,    1,  136,    2, 0x08 /* Private */,
      16,    2,  139,    2, 0x08 /* Private */,
      19,    0,  144,    2, 0x08 /* Private */,
      20,    0,  145,    2, 0x08 /* Private */,
      21,    0,  146,    2, 0x08 /* Private */,
      22,    0,  147,    2, 0x08 /* Private */,
      23,    0,  148,    2, 0x08 /* Private */,
      24,    0,  149,    2, 0x08 /* Private */,
      25,    1,  150,    2, 0x08 /* Private */,
      27,    0,  153,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void,

       0        // eod
};

void ReadingWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ReadingWindow *_t = static_cast<ReadingWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showMainWindow(); break;
        case 1: _t->windowWasResized(); break;
        case 2: _t->saveBookProgress(); break;
        case 3: _t->on_min_button_clicked(); break;
        case 4: _t->on_full_size_button_clicked(); break;
        case 5: _t->on_exit_button_clicked(); break;
        case 6: _t->on_MenuButton_clicked(); break;
        case 7: _t->ContentsButton_clicked(); break;
        case 8: _t->FindButton_Clicked(); break;
        case 9: _t->SettingsButton_Clicked(); break;
        case 10: _t->SynchronizationButton_Clicked(); break;
        case 11: _t->BackToMainWindowButton_Clicked(); break;
        case 12: _t->setStyle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->StartSearch((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 14: _t->NextSearchStep(); break;
        case 15: _t->PrevSearchStep(); break;
        case 16: _t->clockStep(); break;
        case 17: _t->updateProgress(); break;
        case 18: _t->reprintResizedText(); break;
        case 19: _t->reprintNewSettText(); break;
        case 20: _t->goToSection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->saveBookPos(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ReadingWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReadingWindow::showMainWindow)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ReadingWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReadingWindow::windowWasResized)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ReadingWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReadingWindow::saveBookProgress)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ReadingWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ReadingWindow.data,
      qt_meta_data_ReadingWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ReadingWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReadingWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ReadingWindow.stringdata0))
        return static_cast<void*>(const_cast< ReadingWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ReadingWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void ReadingWindow::showMainWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ReadingWindow::windowWasResized()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ReadingWindow::saveBookProgress()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
