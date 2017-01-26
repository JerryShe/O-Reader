#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>

class SearchWindow : public QDialog
{
    Q_OBJECT
public:
    SearchWindow(QPoint position, QString style, bool mode, QWidget * parent = 0);
    ~SearchWindow();

private slots:
    void YepButtonClicked();
    void NopeButtonClicked();
    void exitButtonClicked();
    void TextChanged();

    void setStyle(QString style);

signals:
    void startSearch(QString token, QString searchType);
    void previousResult();
    void nextResult();
    void windowClosed();

private:
    bool workMode;                  // true - окошко поиска, false - виджет поиска
    bool signalWasSended = false;
    QVBoxLayout * VLayout;

    QHBoxLayout * TopLayout;
    QHBoxLayout * TextLayout;
    QHBoxLayout * ButtonLayout;

    QPushButton * exit_button;
    QSpacerItem * topSpacer;
    QPushButton * YepButton;
    QPushButton * NopeButton;

    QLineEdit * TextBox;
    QComboBox * SearchTypeBox;
};

#endif // SEARCHWINDOW_H
