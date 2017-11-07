INCLUDEPATH += $$PWD

include($$PWD/book_page/book_page.pri)
include($$PWD/book_widget/book_widget.pri)
include($$PWD/library_view/library_view.pri)
include($$PWD/widgets/widgets.pri)

SOURCES += $$PWD/*.cpp

HEADERS += $$PWD/*.h

FORMS += $$PWD/*.ui
