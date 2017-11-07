#ifndef RIGHT_CLICK_MENU_H
#define RIGHT_CLICK_MENU_H

#include <QWidget>


namespace Ui {
class RightClickMenu;
}

class RightClickMenu : public QWidget
{
    Q_OBJECT

public:
    explicit RightClickMenu(QWidget *parent = 0);
    ~RightClickMenu();

public slots:
    /// 0 - select disabled, 1 - select enabled, 2 - text selected
    void setState(const int &state);
    void setStyle();

signals:
    void rescaleText(const bool inc);
    void enableSelect();
    void disableSelect();
    void openSearch();
    void findSelected();
    void openSettings();
    void createNote();
    void copySelected();
    void findGoogle();
    void translateGoogle();

private:
    Ui::RightClickMenu *ui;
};

#endif // READING_RIGHT_CLICK_MENU_H
