#include "cache_or_safe_storage.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {



std::unique_ptr<cache_or_safe_storage> cache_or_safe_storage::make(QPointF pos, QColor color)
{
    std::unique_ptr <cache_or_safe_storage> ret (new cache_or_safe_storage);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;

}

cache_or_safe_storage::cache_or_safe_storage(item* parent)
    :item(parent)
{

}

void cache_or_safe_storage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
