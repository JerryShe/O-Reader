#ifndef SEARCH_WINDOW_H
#define SEARCH_WINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

class SearchWindow : public QDialog
{
    Q_OBJECT
public:
    SearchWindow(const QPoint &position, const QString &style, QWidget * parent = 0);
    ~SearchWindow();

private slots:
    void YepButtonClicked();
    void NopeButtonClicked();

    void setStyle(const QString &style);

signals:
    void startSearch(QString token, QString searchType);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    bool searchIsWorking;
    QVBoxLayout * VLayout;

    QHBoxLayout * TopLayout;
    QHBoxLayout * TextLayout;
    QHBoxLayout * ButtonLayout;

    QSpacerItem * topSpacer;
    QPushButton * YepButton;
    QPushButton * NopeButton;

    QLineEdit * TextBox;
    QComboBox * SearchTypeBox;
};

#endif // SEARCH_WINDOW_H
