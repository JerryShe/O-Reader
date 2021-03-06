#include "custom_widgets/answer_dialog.h"
#include "styles.h"
#include "data_handlers/settings_handler.h"


AnswerDialog::AnswerDialog(const QPoint position, const QString text, QWidget *parent)
{
    setParent(parent);
    resize(300,70);
    move(position);

    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint | Qt::Popup);
    setAttribute(Qt::WA_DeleteOnClose);

    yes = new QPushButton(QObject::tr("Yes"), this);
    yes->setFlat(true);
    yes->setFixedHeight(25);

    no = new QPushButton(QObject::tr("No"), this);
    no->setFlat(true);
    no->setFixedHeight(25);

    message = new QLabel(text, this);
    message->setFont(QFont("MS Shell Dlg 2", 12, QFont::Normal));


    QString styles[3];
    setAnswerDialogStyle (styles, SettingsHandler::getSettings()->getInterfaceStyle());
    setStyleSheet(styles[0]);
    yes->setStyleSheet(styles[1]);
    no->setStyleSheet(styles[2]);

    connect(yes, SIGNAL(clicked()), SLOT(accept()));
    connect(no, SIGNAL(clicked()), SLOT(reject()));

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(yes);
    buttonLayout->addWidget(no);

    windowLayout = new QVBoxLayout(this);
    windowLayout->addWidget(message,0,Qt::AlignCenter);
    windowLayout->addLayout(buttonLayout);

    setLayout(windowLayout);
}

AnswerDialog::~AnswerDialog()
{
    delete buttonLayout;
}
