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
    pugixml.cpp

HEADERS  += mainwindow.h \
    pugiconfig.hpp \
    pugixml.hpp

FORMS    += mainwindow.ui

RESOURCES += \
    top_buttons.qrc
