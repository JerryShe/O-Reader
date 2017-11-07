INCLUDEPATH += $$PWD

include($$PWD/data_handlers/data_handlers.pri)
include($$PWD/custom_widgets/custom_widgets.pri)
include($$PWD/login_window/login_window.pri)
include($$PWD/main_window/main_window.pri)
include($$PWD/reading_window/reading_window.pri)

SOURCES += $$PWD/*.cpp

HEADERS += $$PWD/*.h
