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
    BookOrFolder(const QPoint &position, const int &hSize, const QString &Style, QWidget *parent);
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
