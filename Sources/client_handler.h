#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <QObject>

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    static ClientHandler* getClientHandler();

signals:
    void connectionLost();
    void synchronize();

public slots:
    int synchronizeToServer();
    int synchronizeFromServer();

    int connectToServer();
    int disconnectFromServer();
    bool checkConnection();

    bool loginOnServer(const QString &email, const QString &password);
    bool autoLoginOnServer();

    bool signup(const QString &email, const QString &password);
    bool signupConfirm(const QString &code);

    bool changePass(const QString &email);
    bool changeConfirm(const QString &code, const QString& pass);

    QString getUserToken();
    void setUserToken(const QString &token);

private:
    ClientHandler();
    ~ClientHandler();


    QString ServerIP;
    QString ServerPort;

    QString UserToken;
    QString UserEmail;
};

#endif // CLIENT_HANDLER_H
