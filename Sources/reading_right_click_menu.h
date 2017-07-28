#ifndef READING_RIGHT_CLICK_MENU_H
#define READING_RIGHT_CLICK_MENU_H

#include <QWidget>

namespace Ui {
class ReadingRightClickMenu;
}

class ReadingRightClickMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ReadingRightClickMenu(QWidget *parent = 0);
    ~ReadingRightClickMenu();

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
    Ui::ReadingRightClickMenu *ui;
};

#endif // READING_RIGHT_CLICK_MENU_H
