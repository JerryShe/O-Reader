#-------------------------------------------------
#
# Project created by QtCreator 2016-06-27T17:57:22
#
#-------------------------------------------------

QT       += core gui
QT       += xml


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
    books.cpp \
    settings.cpp \
    book_or_folder.cpp \
    settings_programlayout.cpp \
    settings_profilelayout.cpp \
    settings_readerlayout.cpp \
    book_page.cpp \
    genresmap.cpp \
    synchronization.cpp \
    reading_window.cpp \
    search_window.cpp \
    fb2textparser.cpp

HEADERS  += \
    login_window.h \
    main_window.h \
    library_layout.h \
    answer_dialog.h \
    styles.h \
    settings_layout.h \
    synchronization_layout.h \
    books.h \
    settings.h \
    book_or_folder.h \
    settings_programlayout.h \
    settings_profilelayout.h \
    settings_readerlayout.h \
    book_page.h \
    genresmap.h \
    synchronization.h \
    reading_window.h \
    search_window.h \
    fb2textparser.h

FORMS    += mainwindow.ui \
            loginwindow.ui \
    settings_programlayout.ui \
    settings_profilelayout.ui \
    settings_readerlayout.ui \
    book_page.ui \
    readingwindow.ui

RESOURCES += \
    images.qrc



