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
    set_item_type("缓冲或者安全库存");
    return ret;

}

cache_or_safe_storage::cache_or_safe_storage(item* parent)
    :fixed_item (parent)
{
    set_attribute ("产品名称");
    set_attribute ("库存数量");
    set_attribute ("库存周期");

    set_z_value(308);

}

void cache_or_safe_storage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF
    p1_{0.39 * item_width_ ,0.0125 * item_height_},
    p2_{0.60 * item_width_,0.0125 * item_height_},
    p3_{0.39 * item_width_,0.3375 * item_height_},
    p4_{0.60 * item_width_,0.3375 * item_height_},
    p5_{0.39 * item_width_,0.6625 * item_height_},
    p6_{0.60 * item_width_,0.6625 * item_height_},
    p7_{0.39 * item_width_,0.9875 * item_height_},
    p8_{0.6 * item_width_,0.9875 * item_height_};


    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(item_width_ * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::blue);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_,p2_,p8_,p7_}},Qt::WindingFill);
    painter->drawLine(p3_,p4_);
    painter->drawLine(p5_,p6_);
    item::paint(painter, option, widget);

}
}
