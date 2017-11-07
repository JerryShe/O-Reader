greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui xml gui-private

TARGET = OReader

TEMPLATE = app

TRANSLATIONS = Languages/en.ts\
               Languages/ru.ts

RC_FILE = app.rc

RESOURCES += images.qrc

include(Sources/sources.pri)
