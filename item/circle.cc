#include "circle.h"
#include <QPointF>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QRectF>

namespace item {


std::unique_ptr<circle> circle::make(QPointF pos, QColor color)
{
    std::unique_ptr<circle>ret(new circle);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

circle::circle(item *parent)
    :item(parent)
{


}

void circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    //给定坐标
    painter->setBrush(Qt::white);

    painter->drawArc(QRectF{10, 0, 80, 80}, 45 * 16, 270 * 16);
    painter->setBrush(Qt::black);
    painter->drawPolygon({{p1,p2,p3}},Qt::WindingFill);

    item::paint(painter, option, widget);
}

}
