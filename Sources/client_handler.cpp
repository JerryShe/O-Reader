#include "client_handler.h"



ClientHandler* ClientHandler::getClientHandler()
{
    static ClientHandler clientHandler;
    return &clientHandler;
}

ClientHandler::ClientHandler()
{}

ClientHandler::~ClientHandler()
{}


int ClientHandler::synchronizeToServer()
{
    return 0;
}

int ClientHandler::synchronizeFromServer()
{
    return 0;
}

int ClientHandler::connectToServer()
{
    return 1;
}

int ClientHandler::disconnectFromServer()
{
    return 1;
}

bool ClientHandler::checkConnection()
{
    return true;
}

bool ClientHandler::loginOnServer(const QString &email, const QString &password)
{
    return true;
}

bool ClientHandler::autoLoginOnServer()
{
    return true;
}

bool ClientHandler::signup(const QString &email, const QString &password)
{
    return true;
}

bool ClientHandler::signupConfirm(const QString &code)
{
    return true;
}

bool ClientHandler::changePass(const QString &email)
{
    return true;
}

bool ClientHandler::changeConfirm(const QString &code, const QString& pass)
{
    return true;
}

QString ClientHandler::getUserToken()
{
    return UserToken;
}

void ClientHandler::setUserToken(const QString &token)
{
    UserToken = token;
}
