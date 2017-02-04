#include "cache_or_safe_storage.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
///修改好
namespace item {



std::unique_ptr<cache_or_safe_storage> cache_or_safe_storage::make(QPointF pos, QColor color)
{
    std::unique_ptr <cache_or_safe_storage> ret (new cache_or_safe_storage);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "缓冲或者安全库存";
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
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::blue);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_,p2_,p8_,p7_}},Qt::WindingFill);
    painter->drawLine(p3_,p4_);
    painter->drawLine(p5_,p6_);
    item::paint(painter, option, widget);

}
}
