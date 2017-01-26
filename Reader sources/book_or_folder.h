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
    BookOrFolder(QPoint position, int hSize, QString Style, QWidget *parent);
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
