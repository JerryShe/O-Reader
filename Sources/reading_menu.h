#ifndef READING_MENU_H
#define READING_MENU_H

#include <QWidget>

#include <QStateMachine>
#include <QPropertyAnimation>
#include <QSignalTransition>

namespace Ui {
class ReadingMenu;
}

class ReadingMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ReadingMenu(QWidget *parent = 0);
    ~ReadingMenu();

public slots:
    bool menuIsHidden();
    void setStyle();
    void hideMenu();
    void showMenu();

signals:
    void showMainWindow();
    void MenuButtonClicked();
    void showContentsTable();
    void showSettingsWindow();

private slots:
    void on_ContentsButton_clicked();
    void on_SettingsButton_clicked();
    void on_BackButton_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::ReadingMenu *ui;

    QStateMachine *machine;
    QPropertyAnimation *animation;
    QState *s1;
    QState *s2;

    QSignalTransition *transition1;
    QSignalTransition *transition2;
};

#endif // READING_MENU_H
