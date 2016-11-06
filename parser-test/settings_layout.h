#ifndef SETTINGSLAYOUT_H
#define SETTINGSLAYOUT_H

#include <QWidget>
#include <QGridLayout>

class settingslayout : public QWidget
{
    Q_OBJECT
public:
    explicit settingslayout(QWidget *parent = 0);

signals:

public slots:

private:
    QGridLayout *settingsGridLayout;
};

#endif // SETTINGSLAYOUT_H
