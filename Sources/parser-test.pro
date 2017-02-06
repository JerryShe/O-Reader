greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui
QT       += xml

TARGET = Reader

TEMPLATE = app

TRANSLATIONS = Languages/en.ts\
               Languages/ru.ts

RC_FILE = app.rc

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
    synchronization.cpp \
    reading_window.cpp \
    search_window.cpp \
    genresmap.cpp \
    booktableofcontents.cpp \
    libraryhandler.cpp \
    fb2textpaginator.cpp

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
    synchronization.h \
    reading_window.h \
    search_window.h \
    genresmap.h \
    booktableofcontents.h \
    libraryhandler.h \
    fb2textpaginator.h

FORMS    += mainwindow.ui \
            loginwindow.ui \
    settings_programlayout.ui \
    settings_profilelayout.ui \
    settings_readerlayout.ui \
    book_page.ui \
    readingwindow.ui \
    booktableofcontents.ui

RESOURCES += \
    images.qrc
