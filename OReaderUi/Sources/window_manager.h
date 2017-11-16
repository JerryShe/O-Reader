#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <QMainWindow>
#include <QStateMachine>
#include <QHBoxLayout>

#include "main_window.h"
#include "login_window.h"
#include "reading_window.h"

#include "settings_handler.h"
#include "device_settings.h"
#include "synchronization.h"
#include "library_handler.h"
#include "client_handler.h"


class WindowManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowManager(QWidget *parent = 0);
    ~WindowManager();

    void saveProgramData();


public slots:
    void showLoadingImage(QString imageFile);
    void hideLoadingImage();

private slots:
    void showLogin();
    void showMain();
    void hideMain();
    void showReading();

    void showWindowMinimazed();
    void showWindowMaximazed();
    void closeWindow();

signals:
    void showMainWindow();
    void showLoginWindow();
    void showReadingWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    QRect prev_geometry;

    bool moving = false;
    int resizingMethod;
    bool resizing = false;

    QPoint lastClickPoint;

    int resizingFrame = 5;


    QStateMachine* windowMachine;
    QState* loginState;
    QState* mainState;
    QState* readingState;

    MainWindow* mainWindow;
    LoginWindow* loginWindow;
    ReadingWindow* readingWindow;

    QTranslator* LanguageTranslator;

    QThread * HandlerThread;

    Synchronization* UserSynchro;
    SettingsHandler* ProgramSettings;
    DeviceSettingsHandler* DeviceSettings;
    LibraryHandler* LibHandler;
    ClientHandler* clientHandler;



    QWidget* LastWindow;

    QLabel* loadingLabel;
};

#endif // WINDOW_MANAGER_H
