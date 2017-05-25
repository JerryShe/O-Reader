#ifndef BATTERY_WIDGET_H
#define BATTERY_WIDGET_H

#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QPen>


class BatteryWidget : public QLabel
{
    Q_OBJECT

public:
    BatteryWidget(QWidget* parent = 0);
    BatteryWidget(const int &paintMode, const Qt::Orientations orientation, const int &penWidth = 2, const QColor &widgetColor = Qt::black, QWidget *parent = 0);
    BatteryWidget(const QPen &PaintPen, const Qt::Orientations orientation, const int &paintMode = 0, QWidget *parent = 0);

public slots:
    void setPen(const QPen &PaintPen);
    void setColor(const QColor &color);
    void setPenWidth(const int &width);
    void setPaintMode(const int &paintMode);
    void setIconOrientation(const Qt::Orientations orientation);

    QPen getPen() const;
    int getPaintMode() const;
    Qt::Orientations getIconOrientation() const;

    int getBatteryLevel() const;
    int getBatteryStatus() const;

private slots:
    void start();
    void updateWidget();
    void drawHorisontalIcon(QPainter &p, QRect &rect);
    void drawVerticalIcon(QPainter &p, QRect &rect);
    void drawText(QPainter &p, QRect &rect);

protected:
    virtual void paintEvent(QPaintEvent *e);

private:
    QTimer* timer;
    int updateTime;

    QPen pen;
    int mode;                             ///mode: 0 - icon+text, 1 - icon, 2 - text

    int batteryLvl;
    int batteryStatus;                  /// 1 - charging, 2 - normal, 0 - no battery, -1 - unknoun

    bool iconMode;                      /// false - horisontal, true - vertical
};

#endif // BATTERY_WIDGET_H
