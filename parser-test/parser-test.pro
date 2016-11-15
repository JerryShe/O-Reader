#-------------------------------------------------
#
# Project created by QtCreator 2016-06-27T17:57:22
#
#-------------------------------------------------

QT       += core gui
QT += xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = parser-test
TEMPLATE = app


SOURCES += main.cpp\
    main_window.cpp \
    login_window.cpp \
    library_layout.cpp \
    answer_dialog.cpp \
    styles.cpp \
    settings_layout.cpp \
    synchronization_layout.cpp \
    books.cpp

HEADERS  += \
    login_window.h \
    main_window.h \
    library_layout.h \
    answer_dialog.h \
    styles.h \
    settings_layout.h \
    synchronization_layout.h \
    books.h

FORMS    += mainwindow.ui \
    loginwindow.ui

RESOURCES += \
    checkbox.qrc \
    images.qrc



