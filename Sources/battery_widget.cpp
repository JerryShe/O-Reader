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
    iconMode = false;

    start();
}


BatteryWidget::BatteryWidget(const int &paintMode, const Qt::Orientations orientation, const int &penWidth, const QColor &WidgetColor, QWidget* parent) : QLabel(parent)
{
    if (getBatteryStatus() > 0)
        show();
    else
        hide();

    pen.setWidth(penWidth);
    pen.setColor(WidgetColor);

    setPaintMode(paintMode);
    setIconOrientation(orientation);

    start();
}


BatteryWidget::BatteryWidget(const QPen &PaintPen, const Qt::Orientations orientation, const int &paintMode, QWidget* parent) : QLabel(parent)
{
    if (getBatteryStatus() > 0)
        show();
    else
        hide();

    pen = PaintPen;

    setPaintMode(paintMode);
    setIconOrientation(orientation);

    start();
}


void BatteryWidget::start()
{
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


void BatteryWidget::setPaintMode(const int &paintMode)
{
    mode = paintMode;
    if (mode < 0 || mode > 2)
        mode = 0;
}


void BatteryWidget::setIconOrientation(const Qt::Orientations orientation)
{
    if (orientation == Qt::Vertical)
        iconMode = true;
    else
        iconMode = false;
}


QPen BatteryWidget::getPen() const
{
    return pen;
}

int BatteryWidget::getPaintMode() const
{
    return mode;
}


Qt::Orientations BatteryWidget::getIconOrientation() const
{
    if (iconMode)
        return Qt::Vertical;
    return Qt::Horizontal;
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
}


void BatteryWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setPen(pen);

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
    iconRect.setBottom(textRect.bottom() - pen.width()/2 - pen.width()%2 - 1);

    if (mode == 0)
    {
        iconRect.setLeft(iconRect.left() + 3);
        iconRect.setRight(iconRect.x() + this->width()/2);

        textRect.setLeft(iconRect.right() + 3);

        if (iconMode)
            drawVerticalIcon(p, iconRect);
        else
            drawHorisontalIcon(p, iconRect);

        drawText(p, textRect);
    }
    else if (mode == 1)
    {
        iconRect.setLeft(iconRect.left() + 3);
        iconRect.setRight(iconRect.right() - 3);

        if (iconMode)
            drawVerticalIcon(p, iconRect);
        else
            drawHorisontalIcon(p, iconRect);
    }
}


void BatteryWidget::drawHorisontalIcon(QPainter &p, QRect &rect)
{
    int lostPixel = pen.width()%2;

    int width = rect.width(), height = rect.height();
    if (height > width/2)
        height = width/2;
    else if (height < width/2)
        width = height*2;

    QPoint lt, rb;

    lt.setX(rect.x() + (rect.width() - width)/2);
    rb.setX(lt.x() + width - width/10);


    rb.setY(rect.y() + (rect.height() + height)/2);
    lt.setY(rect.y() + (rect.height() - height)/2);

    int penwidth = p.pen().width();

    QPoint plt, prb;
    plt.setX(rb.x() + penwidth);
    plt.setY(lt.y() + (rb.y() - lt.y())/4);
    prb.setX(rb.x() + penwidth + width/10);
    prb.setY(rb.y() - (rb.y() - lt.y())/4);

    QRect pimpRect(plt, prb);

    p.drawRect(QRect(lt, rb));

    p.fillRect(pimpRect, p.pen().color());


    lt.setX(lt.x() + penwidth*1.5 + lostPixel);
    lt.setY(lt.y() + penwidth*1.5 + lostPixel);

    width = rb.x() - penwidth*1.5 - lt.x();


    rb.setX(lt.x() + width*(batteryLvl/100) + lostPixel);
    rb.setY(rb.y() - penwidth*1.5 + lostPixel);


    p.fillRect(QRect(lt, rb), p.pen().color());
}


void BatteryWidget::drawVerticalIcon(QPainter &p, QRect &rect)
{
    int lostPixel = pen.width()%2;


    int width = rect.width(), height = rect.height();
    if (height > width*2)
        height = width*2;
    else if (height < width*2)
        width = height/2;

    QPoint lt, rb;

    lt.setX(rect.x() + (rect.width() - width)/2);
    rb.setX(lt.x() + width);

    rb.setY(rect.y() + (rect.height() + height)/2);
    lt.setY(rect.y() + (rect.height() - height)/2 + height/10);

    int penwidth = p.pen().width();

    QPoint plt, prb;
    plt.setX(rect.x() + (rect.width() - width/2)/2);
    plt.setY(lt.y() - height/10);
    prb.setX(rb.x() - (plt.x() - lt.x()));
    prb.setY(lt.y());

    QRect pimpRect(plt, prb);

    p.drawRect(QRect(lt, rb));

    p.fillRect(pimpRect, p.pen().color());


    rb.setX(rb.x() - penwidth*1.5);
    rb.setY(rb.y() - penwidth*1.5);

    height = rb.y() - penwidth*1.5 - lt .y() - lostPixel;

    lt.setX(lt.x() + penwidth*1.5 + lostPixel*2);
    lt.setY(rb.y() - (height)*(batteryLvl/100.0));


    p.fillRect(QRect(lt, rb), p.pen().color());
}


void BatteryWidget::drawText(QPainter &p, QRect &rect)
{
    p.setFont(this->font());
    p.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(batteryLvl) + "%");
}
