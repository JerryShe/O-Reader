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

private:
    Ui::ReadingRightClickMenu *ui;
};

#endif // READING_RIGHT_CLICK_MENU_H
