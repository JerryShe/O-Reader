#include "search_window.h"
#include "styles.h"
#include <QPushButton>
#include <QListView>


void SearchWindow::setStyle(QString style)
{
    QString styleList[3];
    setSearchWindowStyle(styleList, style);
    YepButton->setStyleSheet(styleList[0]);
    NopeButton->setStyleSheet(styleList[0]);
    TextBox->setStyleSheet(styleList[1]);
    SearchTypeBox->setStyleSheet(styleList[2]);

    setExitButtonStyle(styleList, style);
    exit_button->setStyleSheet(styleList[0]);
}

SearchWindow::SearchWindow(int posX, int posY, QString style, bool mode, QWidget * parent): QDialog(parent)
{
    workMode = mode;
    hide();
    move(posX, posY);
    setWindowFlags(Qt::FramelessWindowHint);

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
    connect(TextBox, SIGNAL(textChanged(QString)), this, SLOT(TextChanged()));
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

    exit_button = new QPushButton(this);
    exit_button->hide();

    QStringList a;
    if (mode == true)
    {
        setFixedSize(400, 80);
        TextBox->setFixedSize(250, 30);
        SearchTypeBox->setFixedSize(150, 30);
        YepButton->setFixedSize(200,25);
        YepButton->setText(QObject::tr("Previous"));
        NopeButton->setFixedSize(200,25);
        NopeButton->setText(QObject::tr("Next"));
        a<<QObject::tr("From the beginning")<<QObject::tr("From the end")<<QObject::tr("From the current position");

        TopLayout->setContentsMargins(0,0,0,0);
        TopLayout->setSpacing(0);
        exit_button->setFixedSize(25,25);

        connect(exit_button, SIGNAL(clicked(bool)), this, SLOT(exitButtonClicked()));

        TopLayout->addSpacerItem(topSpacer);
        TopLayout->addWidget(exit_button, 1);

        exit_button->show();
    }
    else
    {
        setFixedSize(300, 70);
        TextBox->setFixedSize(200, 35);
        SearchTypeBox->setFixedSize(100, 35);
        YepButton->setFixedSize(150,35);
        YepButton->setText(QObject::tr("Find", "button in find window"));
        NopeButton->setFixedSize(150,35);
        NopeButton->setText(QObject::tr("Cancel"));
        a<<QObject::tr("Author")<<QObject::tr("Title")<<QObject::tr("Series");
    }
    SearchTypeBox->addItems(a);
    this->setLayout(VLayout);
    setStyle(style);
    this->show();
}

SearchWindow::~SearchWindow()
{
    delete VLayout;
    delete TopLayout;
    delete TextLayout;
    delete ButtonLayout;
    delete exit_button;
    delete topSpacer;
    delete YepButton;
    delete NopeButton;
    delete TextBox;
    delete SearchTypeBox;
}

void SearchWindow::YepButtonClicked()
{
    if (workMode)
        if (!signalWasSended)
        {
            emit startSearch(TextBox->text(), SearchTypeBox->currentText());
            signalWasSended = true;
        }
        else
            emit previousResult();
    else
    {
        emit startSearch(TextBox->text(), SearchTypeBox->currentText());
        this->hide();
    }
}

void SearchWindow::NopeButtonClicked()
{
    if (workMode)
        if (!signalWasSended)
        {
            emit startSearch(TextBox->text(), SearchTypeBox->currentText());
            signalWasSended = true;
        }
        else
            emit nextResult();
    else
        this->close();
}

void SearchWindow::exitButtonClicked()
{
    emit windowClosed();
    this->close();
}

void SearchWindow::TextChanged()
{
    signalWasSended = false;
}
