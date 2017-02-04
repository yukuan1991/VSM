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
    QPointF
    p1_{0.39 * item_width ,0.0125 * item_height},
    p2_{0.60 * item_width,0.0125 * item_height},
    p3_{0.39 * item_width,0.3375 * item_height},
    p4_{0.60 * item_width,0.3375 * item_height},
    p5_{0.39 * item_width,0.6625 * item_height},
    p6_{0.60 * item_width,0.6625 * item_height},
    p7_{0.39 * item_width,0.9875 * item_height},
    p8_{0.6 * item_width,0.9875 * item_height};


    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::blue);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_,p2_,p8_,p7_}},Qt::WindingFill);
    painter->drawLine(p3_,p4_);
    painter->drawLine(p5_,p6_);
    item::paint(painter, option, widget);

}
}
