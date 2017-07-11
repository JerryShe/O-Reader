#ifndef QTABSWITCHER_H
#define QTABSWITCHER_H

#include <QPushButton>
#include <QWidget>
#include <QSignalMapper>
#include <QSet>


class QTab: public QObject
{
    Q_OBJECT
public:
    QTab(QWidget *Widget, QPushButton *Button, const QString &AStyle = QString(), const QString &IStyle = QString());
    ~QTab(){}

    QPushButton* getButton();
    QWidget* getWidget();
    QString getActiveStyle();
    QString getInactiveStyle();
    bool isHiden();

    void setButton(QPushButton* Button);
    void setWidget(QWidget* Widget);
    void setStyles(QString ActiveStyle, QString InactiveStyle = QString());

public slots:
    void openTab();
    void closeTab();
    void show();
    void hide();

private:
    QPushButton* button;
    QWidget* widget;
    QString activeStyle;
    QString inactiveStyle;
    bool hiden;
};




class QTabSwitcher: public QObject
{
    Q_OBJECT
public:
    QTabSwitcher(QObject* parent = 0);
    ~QTabSwitcher();


public slots:
    void addTab(QWidget* tabWidget, QPushButton* tabButton, const QString &activeStyle = QString(), const QString &inactiveStyle = QString());
    void addTab(QTab* tab);

    void setButtonStyleSheet(const int &tabIndex, const QString &activeStyle = QString(), const QString &inactiveStyle = QString());
    void setButtonStyleSheet(QPushButton* tabButton, QString activeStyle = QString(), QString inactiveStyle = QString());
    void setButtonStyleSheet(QWidget* tabWidget, QString activeStyle = QString(), QString inactiveStyle = QString());

    void removeTab(int tabIndex);
    void removeTab(QPushButton* tabButton);
    void removeTab(QWidget* tabWidget);

    int indexOf(QPushButton* tabButton);
    int indexOf(QWidget* tabWidget);
    int indexOf(QTab* tab);

    int getCurrentTabIndex();
    QTab* getCurrentTab();

    QPushButton* getCurrentButton();
    QWidget* getCurrentWidget();

    int getTabCount();

    void switchTab(const int &tabIndex);
    void switchTab(QPushButton* tabButton);
    void switchTab(QWidget* tabWidget);

    void activateTab(const int &index);
    void activateTab(QPushButton* tabButton);
    void activateTab(QWidget* tabWidget);

    void deactivateTab(int index);
    void deactivateTab(QPushButton* tabButton);
    void deactivateTab(QWidget* tabWidget);

    void start(const int &startTab = 0);
    void start(QPushButton* startTabButton);
    void start(QWidget* startTabWidget);

    bool contains(QPushButton* tabButton);
    bool contains(QWidget* tabWidget);
    bool contains(QTab* tab);

    void clear();

private:
    QList <QTab*> tabList;
    QSignalMapper * SignalMapper;
    int CurrentTab;
};

#endif // QTABSWITCHER_H
