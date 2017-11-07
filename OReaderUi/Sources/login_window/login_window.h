#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QWidget>
#include "data_handlers/client_handler.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_exit_button_clicked();

    void on_login_clicked();
    void on_Recovery_clicked();
    void on_Registration_clicked();

    void setStyle();

    void toMainPage();
    void toSignupPage();
    void toSignupConfPage();
    void toRecoveryPage();
    void toRecoveryConfirmPage();

    bool checkEmail(const QString &email);

signals:
    void showMainWindow();

    void showWindowMinimazed();
    void showWindowMaximazed();
    void closeWindow();

protected:
    void changeEvent(QEvent *event);

private:

    /// 0 - Login
    /// 1 - Registration - email
    /// 2 - Registration - confirm
    /// 3 - Recovery - email
    /// 4 - Recovery - confirm

    int activePage = 0;

    ClientHandler* clientHandler;

    Ui::LoginWindow *ui;

};

#endif // LOGIN_WINDOW_H
