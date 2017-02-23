#include "cache_or_safe_storage.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
///修改好
namespace item {



bool cache_or_safe_storage::init()
{
     set_item_type("缓冲或者安全库存");

     set_attribute ("产品名称");
     set_attribute ("库存数量");
     set_attribute ("库存周期");

     set_z_value(308);

     return true;

}

std::unique_ptr<cache_or_safe_storage> cache_or_safe_storage::make(json data, QPointF pos, item* parent)
{
    std::unique_ptr <cache_or_safe_storage> ret (new cache_or_safe_storage(::move(data), pos, parent));
    if(!ret->init ())
    {
        return nullptr;
    }
    else
    {
        return ret;
    }

}

cache_or_safe_storage::cache_or_safe_storage(json data, QPointF pos, item* parent)
    :fixed_item (::move(data), pos, parent)
{

}

void cache_or_safe_storage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto item_width = width();
    auto item_height = height();
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
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::blue);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_,p2_,p8_,p7_}},Qt::WindingFill);
    painter->drawLine(p3_,p4_);
    painter->drawLine(p5_,p6_);
    fixed_item::paint(painter, option, widget);

}
}
