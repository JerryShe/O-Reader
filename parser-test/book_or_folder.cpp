#include "book_or_folder.h"
#include "styles.h"

#include <QPushButton>

BookOrFolder::BookOrFolder(int pos_x, int pos_y, int hSize, bool mode, QString Style)
{
    BookOrFolder::resize(hSize, 40);
    BookOrFolder::move(pos_x, pos_y);
    BookOrFolder::setWindowFlags(Qt::FramelessWindowHint);
    BookOrFolder::setWindowFlags(Qt::Popup);

    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    bookButton = new QPushButton(QObject::tr("Book"), this);
    folderButton = new QPushButton(QObject::tr("Folder"), this);

    folderButton->setMinimumSize(hSize/2, 40);
    folderButton->setFlat(true);

    bookButton->setMinimumSize(hSize/2, 40);
    bookButton->setFlat(true);

    QString buttonsStyle[2];
    setBookOrFolderStyle(buttonsStyle, Style);

    BookOrFolder::setStyleSheet("BookOrButton{backgroud-color:none; border:none;}");
    bookButton->setStyleSheet(buttonsStyle[0]);
    folderButton->setStyleSheet(buttonsStyle[0]);

    if (mode == true)       // 1 - идет добавление, 0 - удаление
    {
        connect(bookButton, SIGNAL(clicked()), this, SIGNAL(AddBookSignal()));
        connect(folderButton, SIGNAL(clicked()), this, SIGNAL(AddFolderSignal()));
    }
    if (mode == false)
    {
        connect(bookButton, SIGNAL(clicked()), this, SIGNAL(DeleteBookSignal()));
        connect(folderButton, SIGNAL(clicked()), this, SIGNAL(DeleteFolderSignal()));
    }

    layout->addWidget(bookButton, 0);
    layout->addWidget(folderButton, 1);
    BookOrFolder::setLayout(layout);
    BookOrFolder::show();
}

BookOrFolder::~BookOrFolder()
{}
