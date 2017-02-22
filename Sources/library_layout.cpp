#include "library_layout.h"
#include "ui_library_layout.h"

#include "styles.h"

#include "book_or_folder.h"
#include "answer_dialog.h"
#include "book_page.h"

#include <QFileDialog>
#include <QDropEvent>
#include <QMimeData>

#include <QThread>



void LibraryLayout::setStyle()
{
    QString styleSheets[6];
    QString currentStyle = ProgramSettings->getInterfaceStyle();

    setLibraryLayoutButtons(styleSheets, currentStyle);
    ui->_ChangeViewMode->setStyleSheet(styleSheets[0]);
    ui->_Upscale->setStyleSheet(styleSheets[1]);
    ui->_Downscale->setStyleSheet(styleSheets[2]);

    setTabButtonsStyle(styleSheets, currentStyle);
    ui->_Find->setStyleSheet(styleSheets[4]);
    ui->_AddBooks->setStyleSheet(styleSheets[0]);
    ui->_Delete->setStyleSheet(styleSheets[0]);
    ui->_Group->setStyleSheet(styleSheets[2]);
    ui->_Sort->setStyleSheet(styleSheets[2]);
    ui->_SortBox->setStyleSheet(styleSheets[3]);
    ui->_GroupBox->setStyleSheet(styleSheets[3]);

    ui->ShowButton->setStyleSheet(styleSheets[5]);
}


LibraryLayout::LibraryLayout(QWidget *parent) : QWidget(parent), ui(new Ui::LibraryLayout)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    searchWindow = 0;

    ui->_SortBox->setView(new QListView());
    ui->_GroupBox->setView(new QListView());

    LibHandler = LibraryHandler::getLibraryHandler();
    ProgramSettings = Settings::getSettings();

    setStyle();

    if (ProgramSettings->getLibraryReprezentation())
    {
        ui->LibraryView->changeViewMod();
        ui->_ChangeViewMode->setChecked(true);
    }

    ui->LibraryView->setSettingsData();


    connect(ui->LibraryView, SIGNAL(showBookPage(unsigned int)), this, SIGNAL(showBookPage(unsigned int)));

    if (LibHandler->getLastOpenedBook() == 0)
    {
        bookWidget = 0;
        return;
    }

    ui->ShowButton->raise();
    bookWidget = new BookWidget(this);
    bookWidget->move(15, 30);
    connect(ui->ShowButton, SIGNAL(toggled(bool)), bookWidget, SIGNAL(showButtonClicked()));

    connect(bookWidget, SIGNAL(showBookPage(unsigned int)), this, SIGNAL(showBookPage(unsigned int)));
    connect(bookWidget, SIGNAL(startReading(uint)), this, SIGNAL(startReading(uint)));

    connect(this, SIGNAL(showBookPage(unsigned int)), this, SLOT(hideBook()));
}


LibraryLayout::~LibraryLayout()
{
    delete ui;
}


void LibraryLayout::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}


void LibraryLayout::dropEvent(QDropEvent *e)
{
    QStringList fileList;
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString file = url.toLocalFile();
        QFileInfo fileInf (file);
        if (fileInf.isDir())
            LibHandler->AddFolder(file);
        else
            if (fileInf.isFile())
                fileList.append(file);
    }
    if (fileList.size() != 0)
    {
        hideBook();
        hideFind();
        LibHandler->AddBooks(fileList);
    }
}


void LibraryLayout::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}


Library* LibraryLayout::getLibraryWidget()
{
    return ui->LibraryView;
}


void LibraryLayout::on__AddBooks_clicked()
{
    hideBook();
    hideFind();

    BookOrFolder *bookOrFolderAnsw = new BookOrFolder(ui->_AddBooks->mapToGlobal(QPoint(0,ui->_AddBooks->height())),
                                                      ui->_AddBooks->size().width(), ProgramSettings->getInterfaceStyle(), this);

    connect(bookOrFolderAnsw, SIGNAL(AddBookSignal()), this, SLOT(addBooksFromFiles()));
    connect(bookOrFolderAnsw, SIGNAL(AddFolderSignal()), this, SLOT(addBooksFromFolder()));
}


void LibraryLayout::addBooksFromFolder()
{
    QString path = QFileDialog::getExistingDirectory(this, QObject::tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    LibHandler->AddFolder(path);
}


void LibraryLayout::addBooksFromFiles()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, QObject::tr("Open files"), "", "(*.FB2)");
    LibHandler->AddBooks(fileList);
}


void LibraryLayout::on__Delete_clicked()
{
    hideBook();
    hideFind();

    if (ui->LibraryView->getSelectedItemsCount() != 0)
    {
        AnswerDialog *answer_window = new AnswerDialog(ui->_Delete->mapToGlobal(QPoint(ui->_Delete->width() - 300, ui->_Delete->height())),
                                                       QObject::tr("Delete books?"),
                                                       ProgramSettings->getInterfaceStyle(),
                                                       this);
        answer_window->show();

        if (answer_window->exec() == QDialog::Accepted)
            LibHandler->deleteBooks(ui->LibraryView->deleteItems());
        else
            delete answer_window;
    }
}


void LibraryLayout::on__ChangeViewMode_toggled(bool checked)
{
    hideBook();
    ui->LibraryView->changeViewMod();
    ProgramSettings->setLibraryReprezentation(checked);
}


void LibraryLayout::on__Upscale_clicked()
{
    hideBook();
    ui->LibraryView->iconUpscale();
}


void LibraryLayout::on__Downscale_clicked()
{
    hideBook();
    ui->LibraryView->iconDownscale();
}

void LibraryLayout::on__SortBox_activated(const QString &arg1)
{
    hideBook();
    LibHandler->sortBooks(arg1);
}


void LibraryLayout::on__Find_toggled(bool checked)
{
    hideBook();

    if (checked == true)
    {
        searchWindow = new SearchWindow(QPoint(ui->_Find->x(),ui->_Find->y() + ui->_Find->height()),
                                        ProgramSettings->getInterfaceStyle(), false,
                                        this);
        //            _____   ___
        //  \  /\  /    |     |__
        //   \/  \/     |     |
        // MEGA BUG, Wiiiiii

        connect(searchWindow, SIGNAL(startSearch(QString,QString)), LibHandler, SLOT(findBooks(QString, QString)));
        connect(searchWindow, SIGNAL(finished(int)), this, SLOT(hideFind()));
    }
    else
    {
        qDebug()<<"find close";
        if (searchWindow != 0)
        {
            searchWindow->close();
            searchWindow = 0;
        }
        LibHandler->refreshLibrary();
    }
}


void LibraryLayout::hideFind()
{
    ui->_Find->setChecked(false);
}


void LibraryLayout::hideBook()
{
    if(!ui->ShowButton->isChecked())
        ui->ShowButton->setChecked(true);
}


Book* LibraryLayout::getBookByIndex(const unsigned int &index)
{
    return LibHandler->getBookByIndex(index);
}


void LibraryLayout::deleteBook(const unsigned int &index)
{
    LibHandler->deleteBook(index);
}


void LibraryLayout::on_ShowButton_clicked()
{
    hideFind();
}
