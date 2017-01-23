#include "reclaimer.h"
#include <QPointF>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QRectF>
///取料看板

namespace item {


std::unique_ptr<reclaimer> reclaimer::make(QPointF pos, QColor color)
{
    std::unique_ptr<reclaimer>ret(new reclaimer);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

reclaimer::reclaimer(item *parent)
    :item(parent)
{


}

void reclaimer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(1.0);
    painter->setPen(the_pen);

    //给定坐标
    //painter->setBrush(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1, p5, p7, p14, p10}});
    painter->drawLine(p2,p8);
    painter->drawLine(p3,p9);
    painter->drawLine(p4,p11);
    painter->drawLine(p6,p12);
    painter->drawLine(p7,p13);
    item::paint(painter, option, widget);
}

}
