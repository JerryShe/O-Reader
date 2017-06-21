#ifndef SEARCH_WINDOW_H
#define SEARCH_WINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>

class SearchWindow : public QDialog
{
    Q_OBJECT
public:
    SearchWindow(const QPoint &position, const QString &style, const bool &mode, QWidget * parent = 0);
    ~SearchWindow();

private slots:
    void YepButtonClicked();
    void NopeButtonClicked();

    void searchStop();
    void searchStart();

    void setStyle(const QString &style);

signals:
    void startSearch(QString token, QString searchType);
    void searchKeyChanged();
    void previousResult();
    void nextResult();

private:
    bool workMode;                  // true - окошко поиска, false - виджет поиска
    bool searchIsWorking;
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

#endif // SEARCH_WINDOW_H
