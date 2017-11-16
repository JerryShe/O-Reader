#include "main_window/library/library_layout.h"
#include "ui_library_layout.h"
#include "main_window/library/widgets/book_or_folder.h"
#include "custom_widgets/answer_dialog.h"
#include "main_window/library/book_page/book_page.h"

#include "styles.h"

#include <QFileDialog>
#include <QDropEvent>
#include <QMimeData>
#include <QScroller>
#include <QFileDialog>
#include <QSlider>
#include <QWidgetAction>
#include <QMenu>

void LibraryLayout::setStyle()
{
    QString styleSheets[7];
    QString currentStyle = ProgramSettings->getInterfaceStyle();

    setLibraryLayoutButtons(styleSheets, currentStyle);
    ui->_ChangeViewMode->setStyleSheet(styleSheets[0]);
    ui->_Downscale->setStyleSheet(styleSheets[2]);

    setTabButtonsStyle(styleSheets, currentStyle);
    ui->_Find->setStyleSheet(styleSheets[4]);
    ui->_AddBooks->setStyleSheet(styleSheets[0]);
    ui->_Delete->setStyleSheet(styleSheets[0]);
    ui->_Group->setStyleSheet(styleSheets[2]);
    ui->_Sort->setStyleSheet(styleSheets[2]);
    ui->_SortDirection->setStyleSheet(styleSheets[6]);
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
    ProgramSettings = SettingsHandler::getSettings();

    setStyle();

    ui->Library_View->loadSettingsData();

    ui->_ChangeViewMode->setChecked(ui->Library_View->getLibraryRepresentation());
    ui->_SortDirection->setChecked(DeviceSettingsHandler::getDeviceSettings()->getLibrarySortOrder());
    ui->_SortBox->setCurrentIndex(DeviceSettingsHandler::getDeviceSettings()->getLibrarySortType());

    connect(ui->Library_View, SIGNAL(showBookPage(QString)), this, SIGNAL(showBookPage(QString)));

    if (LibHandler->getLastOpenedBook() == 0)
    {
        bookWidget = nullptr;
        ui->ShowButton->setEnabled(false);
        ui->ShowButton->hide();
        return;
    }

    ui->ShowButton->raise();
    bookWidget = new BookWidget(this);
    bookWidget->move(15, 30);
    connect(ui->ShowButton, SIGNAL(toggled(bool)), bookWidget, SIGNAL(showButtonClicked()));
    connect(ui->ShowButton, SIGNAL(clicked(bool)), this, SLOT(hideFind()));

    connect(bookWidget, SIGNAL(showBookPage(QString)), this, SIGNAL(showBookPage(QString)));
    connect(bookWidget, SIGNAL(showBookPage(QString)), this, SLOT(hideBookWidget()));
    connect(bookWidget, SIGNAL(startReading(QString)), this, SIGNAL(startReading(QString)));

    connect(this, SIGNAL(showBookPage(QString)), this, SLOT(hideBookWidget()));
    connect(ui->_Find, SIGNAL(toggled(bool)), this, SLOT(hideBookWidget()));
    connect(ui->_ChangeViewMode, SIGNAL(toggled(bool)), this, SLOT(hideBookWidget()));


    connect(LibHandler, SIGNAL(lostBooks(QVector<Book*>)), this, SLOT(lostBooks(QVector<Book*>)));
    connect(ui->Library_View, SIGNAL(clicked(QModelIndex)), this, SLOT(hideBookWidget()));

    connect(ui->_SortDirection, SIGNAL(toggled(bool)), this, SLOT(updateViewSort()));
    connect(ui->_SortBox, SIGNAL(activated(int)), this, SLOT(updateViewSort()));


    if (QTouchDevice::devices().size())
    {
        QScroller::grabGesture(ui->_GroupBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->_GroupBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        QScroller::grabGesture(ui->_SortBox->view()->viewport(), QScroller::LeftMouseButtonGesture);
        ui->_SortBox->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    }

    this->installEventFilter(this);
    ui->Library_View->installEventFilter(this);
}


LibraryLayout::~LibraryLayout()
{
    delete ui;
}


bool LibraryLayout::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)

    switch (event->type())
    {
    case QEvent::Drop:
    {
        QDropEvent *e = static_cast<QDropEvent*>(event);
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
            hideBookWidget();
            hideFind();
            LibHandler->AddBooks(fileList);
        }
        return true;
    }
    case QEvent::DragEnter:
    {
        QDragEnterEvent *e = static_cast<QDragEnterEvent*>(event);
        if (e->mimeData()->hasUrls())
            e->acceptProposedAction();
        return true;
    }
    case QEvent::LanguageChange:
    {
        ui->retranslateUi(this);
        return true;
    }
    case QEvent::KeyPress:
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Delete)
            on__Delete_clicked();
        else if (keyEvent->modifiers() & Qt::CTRL)
        {
            switch (keyEvent->key()) {
            case Qt::Key_F:
            {
                if (!ui->_Find->isChecked())
                    ui->_Find->setChecked(true);
                break;
            }
            case Qt::Key_B:
            {
                addBooksFromFiles();
                break;
            }
            case Qt::Key_D:
            {
                addBooksFromFolder();
                break;
            }
            case Qt::Key_Plus: case Qt::Key_Equal:
            {
                if (ui->Library_View->getBookIconSize() < 348)
                    ui->Library_View->setBookIconSize(ui->Library_View->getBookIconSize() + 2);
                break;
            }
            case Qt::Key_Minus:
            {
                if (ui->Library_View->getBookIconSize() > 112)
                    ui->Library_View->setBookIconSize(ui->Library_View->getBookIconSize() - 2);
                break;
            }
            case Qt::Key_V:
            {
                ui->Library_View->changeViewMod();
                break;
            }
            default:
                return false;
            }
            return true;
        }
        else if (keyEvent->key() == Qt::Key_Escape)
        {
            if (ui->_Find->isChecked())
                ui->_Find->setChecked(false);
            hideBookWidget();
        }

        return true;
    }
    default:
        break;
    }

    return false;
}


void LibraryLayout::lostBooks(QVector <Book*> losted)
{

}


LibraryView* LibraryLayout::getLibraryWidget() const
{
    return ui->Library_View;
}


void LibraryLayout::on__AddBooks_clicked()
{
    hideBookWidget();
    hideFind();

    BookOrFolder *bookOrFolderAnsw = new BookOrFolder(ui->_AddBooks->mapToGlobal(QPoint(0,ui->_AddBooks->height())),
                                                      ui->_AddBooks->size().width(), ProgramSettings->getInterfaceStyle(), this);

    connect(bookOrFolderAnsw, SIGNAL(AddBookSignal()), this, SLOT(addBooksFromFiles()));
    connect(bookOrFolderAnsw, SIGNAL(AddFolderSignal()), this, SLOT(addBooksFromFolder()));
}


void LibraryLayout::addBooksFromFolder()
{
    //TODO: убрать баг с невалидными директориями (компьютер)
    QString path = QFileDialog::getExistingDirectory(this, QObject::tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    LibHandler->AddFolder(path);
}


void LibraryLayout::addBooksFromFiles()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, QObject::tr("Open files"), "", tr("Book files (*.fb2 *.zip *.epub)"));
    LibHandler->AddBooks(fileList);
}


void LibraryLayout::on__Delete_clicked()
{
    hideBookWidget();
    hideFind();

    if (ui->Library_View->getSelectedItemsCount() != 0)
    {
        AnswerDialog *answer_window = new AnswerDialog(ui->_Delete->mapToGlobal(QPoint(ui->_Delete->width() - 300, ui->_Delete->height())),
                                                       QObject::tr("Delete books?"),
                                                       this);
        answer_window->show();

        if (answer_window->exec() == QDialog::Accepted)
        {
            QVector <QString> books = ui->Library_View->deleteSelectedItems();
            for (int i = 0; i < books.size(); i++)
                deleteBook(books[i]);
        }
    }
}


void LibraryLayout::on__ChangeViewMode_toggled(bool checked)
{
    Q_UNUSED(checked)
    ui->Library_View->changeViewMod();
}


void LibraryLayout::on__Downscale_clicked()
{
    hideBookWidget();

    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->move(ui->_Downscale->mapToGlobal(QPoint(-3, ui->_Downscale->height() - 3)));

    QSlider* slider = new QSlider(Qt::Vertical, menu);
    slider->setRange(110, 350);
    slider->setValue(ui->Library_View->getBookIconSize());
    slider->setFixedSize(ui->_Downscale->width(), 100);
    slider->setStyleSheet("QSlider::groove:vertical {"
                     "border: none;"
                     "background-color:rgb(70,0,30);"
                     "width:30px;"
                     "margin-top:-4px;}"

                      "QSlider::handle:vertical {"
                      "background-color: white;"
                      "border: none;"
                      "height: 15px;}");

    QWidgetAction *widAct = new QWidgetAction(menu);
    widAct->setDefaultWidget(slider);

    menu->setAttribute(Qt::WA_TranslucentBackground);
    menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    menu->setStyleSheet("QMenu{background:rgba(0, 0, 0, 0);}");

    connect(slider, SIGNAL(sliderMoved(int)), ui->Library_View, SLOT(setBookIconSize(int)));

    menu->addAction(widAct);
    menu->show();
}


void LibraryLayout::updateViewSort()
{
    hideBookWidget();
    ui->Library_View->setSort(ui->_SortBox->currentText(), ui->_SortDirection->isChecked());

    DeviceSettingsHandler::getDeviceSettings()->setLibrarySortType(ui->_SortBox->currentIndex());
    DeviceSettingsHandler::getDeviceSettings()->setLibrarySortOrder(ui->_SortDirection->isChecked());
}


void LibraryLayout::on__Find_toggled(bool checked)
{
    if (checked == true)
    {
        searchWindow = new SearchWindow(QPoint(ui->_Find->x(),ui->_Find->y() + ui->_Find->height()),
                                        ProgramSettings->getInterfaceStyle(), this);
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
        LibHandler->clearFind();
    }
}


void LibraryLayout::hideFind()
{
    ui->_Find->setChecked(false);
}


void LibraryLayout::hideBookWidget()
{
    ui->ShowButton->setChecked(true);
}


Book* LibraryLayout::getBookByIndex(const QString &index) const
{
    return LibHandler->getBookByIndex(index);
}


void LibraryLayout::deleteBook(QString index)
{
    if (LibHandler->getLastOpenedBook() != 0 && bookWidget != nullptr)
        if (index == bookWidget->getBookIndex())
        {
            hideBookWidget();
            delete bookWidget;
            bookWidget = nullptr;
            ui->ShowButton->setEnabled(false);
            ui->ShowButton->hide();
        }

    LibHandler->deleteBook(index);
}
