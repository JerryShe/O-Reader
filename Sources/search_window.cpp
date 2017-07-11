#include "search_window.h"
#include "styles.h"
#include <QPushButton>
#include <QListView>
#include <QEvent>

#include <QDebug>

#include <QProcess>


void SearchWindow::setStyle(const QString &style)
{
    QString styleList[4];

    setSearchWindowStyle(styleList, style);
    YepButton->setStyleSheet(styleList[0]);
    NopeButton->setStyleSheet(styleList[0]);
    TextBox->setStyleSheet(styleList[1]);
    SearchTypeBox->setStyleSheet(styleList[2]);

    this->setStyleSheet("background-color:rgb(150, 0, 60);");
}

SearchWindow::SearchWindow(const QPoint &position, const QString &style, QWidget * parent): QDialog(parent)
{
    this->parentWidget()->installEventFilter(this);

    move(position);
    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);

    VLayout = new QVBoxLayout(this);
    VLayout->setContentsMargins(0,0,0,0);
    VLayout->setSpacing(0);

    TopLayout = new QHBoxLayout();
    topSpacer = new QSpacerItem(40, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

    TextLayout = new QHBoxLayout();
    TextLayout->setContentsMargins(0,0,0,0);
    TextLayout->setSpacing(0);

    ButtonLayout = new QHBoxLayout();
    ButtonLayout->setContentsMargins(0,0,0,0);
    ButtonLayout->setSpacing(0);

    TextBox = new QLineEdit(this);
    SearchTypeBox = new QComboBox(this);
    SearchTypeBox->setView(new QListView());
    TextLayout->addWidget(TextBox, 0);
    TextLayout->addWidget(SearchTypeBox, 1);

    VLayout->addLayout(TopLayout, 0);
    VLayout->addLayout(TextLayout, 1);
    VLayout->addLayout(ButtonLayout, 2);

    YepButton = new QPushButton(this);
    NopeButton = new QPushButton(this);

    ButtonLayout->addWidget(YepButton, 0);
    ButtonLayout->addWidget(NopeButton, 1);
    connect(YepButton, SIGNAL(clicked(bool)), this, SLOT(YepButtonClicked()));
    connect(NopeButton, SIGNAL(clicked(bool)), this, SLOT(NopeButtonClicked()));


    setFixedSize(300, 70);
    TextBox->setFixedSize(200, 35);
    SearchTypeBox->setFixedSize(100, 35);
    YepButton->setFixedSize(150,35);
    YepButton->setText(QObject::tr("Find", "button in find window"));
    NopeButton->setFixedSize(150,35);
    NopeButton->setText(QObject::tr("Cancel"));

    QStringList types;
    types<<QObject::tr("Author")<<QObject::tr("Title");//<<QObject::tr("Series");

    SearchTypeBox->addItems(types);
    this->setLayout(VLayout);
    setStyle(style);

    this->show();
}


SearchWindow::~SearchWindow()
{
    qDebug()<<"delete search window";
    delete TopLayout;
    delete TextLayout;
    delete ButtonLayout;
}


bool SearchWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize)
    {
        this->move(0, this->parentWidget()->height() - this->height());
    }
    return false;
}


void SearchWindow::YepButtonClicked()
{
    if (TextBox->text().isEmpty())
        return;

    emit startSearch(TextBox->text(), SearchTypeBox->currentText());
    this->hide();
}


void SearchWindow::NopeButtonClicked()
{
    this->close();
}
