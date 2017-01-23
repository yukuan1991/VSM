#include "buffer.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {



std::unique_ptr<buffer> buffer::make(QPointF pos, QColor color)
{
    std::unique_ptr <buffer> ret (new buffer);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;

}

buffer::buffer(item* parent)
    :item(parent)
{

}

void buffer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    painter->setPen(the_pen);
    painter->setBrush(Qt::blue);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1,p2,p4,p3}},Qt::WindingFill);
    painter->drawLine(p5,p6);
    painter->drawLine(p7,p8);
    item::paint(painter, option, widget);

}
}
