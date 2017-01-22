#ifndef BOOKORFOLDER_H
#define BOOKORFOLDER_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QPoint>
#include <QDialog>

class BookOrFolder : public QDialog
{
    Q_OBJECT
public:
    BookOrFolder(int pos_x, int pos_y, int hSize, bool mode, QString Style);
    ~BookOrFolder();

signals:
    void AddBookSignal();
    void AddFolderSignal();
    void DeleteBookSignal();
    void DeleteFolderSignal();

private:    
    QHBoxLayout *layout;
    QPushButton *bookButton;
    QPushButton *folderButton;
};

#endif // BOOKORFOLDER_H
