INCLUDEPATH += $$PWD

include($$PWD/library/library.pri)
include($$PWD/settings/settings.pri)
include($$PWD/synchronization/synchronization.pri)

SOURCES += $$PWD/*.cpp

HEADERS += $$PWD/*.h

FORMS += $$PWD/*.ui
