#-------------------------------------------------
#
# Project created by QtCreator 2016-06-27T17:57:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = parser-test
TEMPLATE = app


SOURCES += main.cpp\
    pugixml.cpp \
    main_window.cpp \
    login_window.cpp \
    library_layout.cpp \
    book_bar.cpp \
    answer_dialog.cpp \
    styles.cpp

HEADERS  += \
    pugiconfig.hpp \
    pugixml.hpp \
    login_window.h \
    main_window.h \
    book_bar.h \
    library_layout.h \
    answer_dialog.h \
    styles.h

FORMS    += mainwindow.ui \
    loginwindow.ui

RESOURCES += \
    checkbox.qrc \
    images.qrc
