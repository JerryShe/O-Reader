greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui xml gui-private

TARGET = O`Reader

TEMPLATE = app

TRANSLATIONS = Languages/en.ts\
               Languages/ru.ts

RC_FILE = app.rc

SOURCES += main.cpp\
    answer_dialog.cpp \
    styles.cpp \
    settings_layout.cpp \
    books.cpp \
    settings.cpp \
    book_or_folder.cpp \
    settings_programlayout.cpp \
    settings_profilelayout.cpp \
    settings_readerlayout.cpp \
    book_page.cpp \
    synchronization.cpp \
    genresmap.cpp \
    library_layout.cpp \
    library_handler.cpp \
    QTabSwitcher.cpp \
    main_window.cpp \
    login_window.cpp \
    reading_window.cpp \
    window_manager.cpp \
    synchronization_layout.cpp \
    book_widget.cpp \
    client_handler.cpp \
    reading_menu.cpp \
    settings_readerlayoutstyle.cpp \
    library_view.cpp \
    book_image_table.cpp \
    battery_widget.cpp \
    book_table_of_contents.cpp \
    search_window.cpp \
    paginator_helper.cpp \
    xml_text_paginator.cpp \
    fb2_parser.cpp \
    tags_resolver.cpp \
    xml_text_parser.cpp \
    xml_text_searcher.cpp \
    library_list_delegate.cpp \
    library_list_proxy_model.cpp \
    library_list_model.cpp

HEADERS  += \
    answer_dialog.h \
    styles.h \
    settings_layout.h \
    books.h \
    settings.h \
    book_or_folder.h \
    settings_programlayout.h \
    settings_profilelayout.h \
    settings_readerlayout.h \
    book_page.h \
    synchronization.h \
    search_window.h \
    genresmap.h \
    library_layout.h \
    library_handler.h \
    QTabSwitcher.h \
    reading_window_копия.h \
    main_window.h \
    login_window.h \
    reading_window.h \
    window_manager.h \
    synchronization_layout.h \
    book_widget.h \
    client_handler.h \
    reading_menu.h \
    settings_readerlayoutstyle.h \
    library_view.h \
    book_image_table.h \
    battery_widget.h \
    book_table_of_contents.h \
    paginator_helper.h \
    tags_resolver.h \
    xml_text_paginator.h \
    xml_text_parser.h \
    fb2_parser.h \
    xml_text_searcher.h \
    library_list_delegate.h \
    library_list_proxy_model.h \
    library_list_model.h

FORMS    += \
    settings_programlayout.ui \
    settings_profilelayout.ui \
    settings_readerlayout.ui \
    book_page.ui \
    booktableofcontents.ui \
    library_layout.ui \
    main_window.ui \
    login_window.ui \
    reading_window.ui \
    synchronization_layout.ui \
    book_widget.ui \
    reading_menu.ui \
    settings_readerlayoutstyle.ui

RESOURCES += \
    images.qrc
