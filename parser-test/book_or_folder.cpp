#include "book_or_folder.h"
#include "styles.h"

#include <QPushButton>

BookOrFolder::BookOrFolder(QPoint position, int hSize, QString Style, QWidget *parent)
{
    setParent(parent);
    resize(hSize, 40);
    move(position);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::Popup);

    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    bookButton = new QPushButton(QObject::tr("Book"), this);
    folderButton = new QPushButton(QObject::tr("Folder"), this);

    folderButton->setMinimumSize(hSize/2, 40);
    bookButton->setFixedSize(hSize/2, 40);

    QString buttonsStyle[2];
    setBookOrFolderStyle(buttonsStyle, Style);

    setStyleSheet("BookOrButton{backgroud-color:none; border:none;}");
    bookButton->setStyleSheet(buttonsStyle[0]);
    folderButton->setStyleSheet(buttonsStyle[0]);

    connect(bookButton, SIGNAL(clicked()), this, SIGNAL(AddBookSignal()));
    connect(folderButton, SIGNAL(clicked()), this, SIGNAL(AddFolderSignal()));

    layout->addWidget(bookButton, 0);
    layout->addWidget(folderButton, 1);
    setLayout(layout);
    show();
}

BookOrFolder::~BookOrFolder()
{}
