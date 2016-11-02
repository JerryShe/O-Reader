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
        mainwindow.cpp \
    pugixml.cpp \
    loginwindow.cpp \
    librarylayout.cpp \
    answerdialog.cpp \
    bookbar.cpp

HEADERS  += mainwindow.h \
    pugiconfig.hpp \
    pugixml.hpp \
    loginwindow.h \
    librarylayout.h \
    answerdialog.h \
    menubuttonsstyles.h \
    bookbar.h

FORMS    += mainwindow.ui \
    loginwindow.ui

RESOURCES += \
    top_buttons.qrc \
    menu_buttons.qrc \
    checkbox.qrc
