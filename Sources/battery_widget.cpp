#include "battery_widget.h"

#include <QColor>
#include <QPainter>

#include <QDebug>

#ifdef Q_OS_LINUX

#else
    #ifdef Q_OS_MAC

    #else
        #ifdef Q_OS_WIN
             #include "windows.h"
        #endif
    #endif
#endif



BatteryWidget::BatteryWidget(QWidget* parent) : QLabel(parent)
{
    if (getBatteryStatus() > 0)
        show();
    else
        hide();

    pen.setWidth(1);
    pen.setColor(Qt::white);

    mode = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWidget()));
    timer->start(2000);
}


BatteryWidget::BatteryWidget(const int &paintMode, const int &penWidth, const QColor &WidgetColor, QWidget* parent) : QLabel(parent)
{
    if (getBatteryStatus() > 0)
        show();
    else
        hide();

    pen.setWidth(penWidth);
    pen.setColor(WidgetColor);

    mode = paintMode;
    if (mode < 0 || mode > 2)
        mode = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWidget()));
    timer->start(2000);
}


BatteryWidget::BatteryWidget(const QPen &PaintPen, const int &paintMode, QWidget* parent) : QLabel(parent)
{
    if (getBatteryStatus() > 0)
        show();
    else
        hide();

    pen = PaintPen;

    mode = paintMode;
    if (mode < 0 || mode > 2)
        mode = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWidget()));
    timer->start(2000);
}


void BatteryWidget::setPen(const QPen &PaintPen)
{
    pen = PaintPen;
}


void BatteryWidget::setColor(const QColor &color)
{
    pen.setColor(color);
}


void BatteryWidget::setPenWidth(const int &width)
{
    pen.setWidth(width);
}


QPen BatteryWidget::getPen()
{
    return pen;
}


int BatteryWidget::getBatteryLevel() const
{
    int lvl = -1;

    #ifdef Q_OS_LINUX
    lvl = -1;
    #else
        #ifdef Q_OS_MAC
        lvl = -1;
        #else
            #ifdef Q_OS_WIN
                 SYSTEM_POWER_STATUS stat;
                 if (GetSystemPowerStatus(&stat))
                     lvl = stat.BatteryLifePercent;
            #endif
        #endif
    #endif

    return lvl;
}


int BatteryWidget::getBatteryStatus() const
{
    int status = -1;

    #ifdef Q_OS_LINUX
    status = -1;
    #else
        #ifdef Q_OS_MAC
        status = -1;
        #else
            #ifdef Q_OS_WIN
                 SYSTEM_POWER_STATUS stat;
                 if (GetSystemPowerStatus(&stat))
                     switch (stat.BatteryFlag)
                     {
                     case 8:
                         status = 1;
                         break;
                     case 128:
                         status = 0;
                         break;
                     case 255:
                         status = -1;
                         break;
                     default:
                         status = 1;
                         break;
                     }
            #endif
        #endif
    #endif

    return status;
}


void BatteryWidget::updateWidget()
{
    if (batteryLvl != getBatteryLevel() || batteryStatus != getBatteryStatus())
    {
        batteryLvl = getBatteryLevel();
        batteryStatus = getBatteryStatus();
        repaint();
    }
    repaint();
}


void BatteryWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setPen(pen);
    //qDebug()<<asd;


    QRect textRect = this->rect();
    textRect.setTop(textRect.top() + 3);
    textRect.setBottom(textRect.bottom() - 3);
    textRect.setRight(textRect.right() - 3);



    if (mode == 2)
    {
        textRect.setLeft(textRect.left() + 3);
        drawText(p, textRect);
        return;
    }

    QRect iconRect = this->rect();
    iconRect.setTop(textRect.top());
    iconRect.setBottom(textRect.bottom());

    if (mode == 0)
    {
        int height = this->rect().height();
        int width = height/2 + 6;

        iconRect.setLeft(iconRect.left() + 3);
        iconRect.setRight(iconRect.x() + width);

        textRect.setLeft(iconRect.right() + 6);

        drawIcon(p, iconRect);
        drawText(p, textRect);
    }
    else if (mode == 1)
    {
        iconRect.setLeft(iconRect.left() + 3);
        iconRect.setRight(iconRect.right() - 3);
        drawIcon(p, iconRect);
    }
}


void BatteryWidget::drawIcon(QPainter &p, QRect &rect)
{
    int lostPixel = 0;
    if (pen.width()%2 == 1)
        lostPixel = 1;

    int width = rect.width(), height = rect.height();
    if (height > width*2)
        height = width*2;
    else if (height < width*2)
        width = height/2;

    QPoint lt, lb, rt, rb;

    lt.setX(rect.x() + (rect.width() - width)/2);
    lb.setX(lt.x());

    rt.setX(lt.x() + width);
    rb.setX(rt.x());


    lb.setY(rect.y() + (rect.height() + height)/2);
    rb.setY(lb.y());

    lt.setY(rect.y() + (rect.height() - height)/2 + height/6);
    rt.setY(lt.y());

    int penwidth = p.pen().width();

    QPoint plt, prb;
    plt.setX(rect.x() + (rect.width() - width/2)/2);
    plt.setY(lt.y() - height/6);
    prb.setX(rt.x() - (plt.x() - lt.x()));
    prb.setY(lt.y());

    QRect pimpRect(plt, prb);

    p.drawLine(lt, lb);
    p.drawLine(lb, rb);
    p.drawLine(rb, rt);
    p.drawLine(rt, lt);

    p.fillRect(pimpRect, p.pen().color());


    rb.setX(rb.x() - penwidth*1.5);
    rb.setY(rb.y() - penwidth*1.5);


    height = rb.y() - penwidth*1.5 - lt .y() - lostPixel;

    lt.setX(lt.x() + penwidth*1.5 + lostPixel);
    lt.setY(rb.y() - (height)*(batteryLvl/100.0));
    qDebug()<<"wtf "<<((height)*(batteryLvl/100.0));
    //asd -= 2;

    p.fillRect(QRect(lt, rb), p.pen().color());
}


void BatteryWidget::drawText(QPainter &p, QRect &rect)
{
    p.setFont(this->font());
    p.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, QString::number(batteryLvl) + "%");
}
