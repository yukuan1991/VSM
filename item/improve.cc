#include "improve.h"
#include <QPointF>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QRectF>
///改善

namespace item {


std::unique_ptr<improve> improve::make(QPointF pos, QColor color)
{
    std::unique_ptr<improve>ret(new improve);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

improve::improve(item *parent)
    :item(parent)
{


}

void improve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(1.0);
    painter->setPen(the_pen);

    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawLine(p1,p2);
    painter->drawLine(p2,p3);
    painter->drawLine(p3,p4);
    painter->drawLine(p4,p5);
    painter->drawLine(p5,p6);
    painter->drawLine(p6,p7);
    painter->drawLine(p7,p8);
    painter->drawLine(p8,p9);
    painter->drawLine(p9,p10);
    painter->drawLine(p10,p11);
    painter->drawLine(p11,p12);
    painter->drawLine(p12,p13);
    painter->drawLine(p13,p14);
    painter->drawLine(p14,p15);
    painter->drawLine(p15,p16);
    painter->drawLine(p16,p17);
    painter->drawLine(p17,p18);
    painter->drawLine(p17,p19);
    painter->drawLine(p19,p20);
    painter->drawLine(p20,p1);


    item::paint(painter, option, widget);
}

}
