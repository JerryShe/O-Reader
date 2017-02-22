#ifndef SETTINGS_READERLAYOUTSTYLE_H
#define SETTINGS_READERLAYOUTSTYLE_H

#include <QWidget>
#include <settings.h>

namespace Ui {
class Settings_ReaderLayoutStyle;
}

class Settings_ReaderLayoutStyle : public QWidget
{
    Q_OBJECT

public:
    explicit Settings_ReaderLayoutStyle(QWidget *parent = 0);
    ~Settings_ReaderLayoutStyle();

public slots:
    QString getHTMLStyle();

    void setStyleName(const QString &name);
    void setStyleData(const TextStyleSheet &style);
    TextStyleSheet getStyleData();

private slots:
    void on_ColorBox_clicked();
    void on_ShowButton_clicked();

signals:
    void settingsUpdate();

private:
    Ui::Settings_ReaderLayoutStyle *ui;
};

#endif // SETTINGS_READERLAYOUTSTYLE_H
