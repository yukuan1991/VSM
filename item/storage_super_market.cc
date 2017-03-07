#include "storage_super_market.h"
#include <memory>
#include <QDebug>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
///修改好
namespace item {


std::unique_ptr<storage_super_market> storage_super_market::make(json data, QPointF pos, abstract_item* parent)
{
    std::unique_ptr <storage_super_market> ret(new storage_super_market(::move(data),pos, parent));
    if(! ret->init ())
    {
        return nullptr;
    }
    else
    {
        return ret;
    }
}

storage_super_market::storage_super_market(json data, QPointF pos, abstract_item* parent)
    :fixed_item(::move(data), pos, parent)
{

}

bool storage_super_market::init()
{
    enable_attribute ("产品名");
    enable_attribute ("数量");

    set_z_value(306);
    set_item_type("库存超市");

    return true;

}

void storage_super_market::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    auto item_width = width();
    auto item_height = height();
    QPointF
    p1_ {0.29 * item_width, 0.0125 * item_height},//p1
    p2_ {0.71 * item_width, 0.0125 * item_height},//p2
    p3_ {0.29 * item_width, 0.3375 * item_height},//
    p4_ {0.71 * item_width, 0.3375 * item_height},

    p5_ {0.29 * item_width, 0.6625 * item_height},
    p6_ {0.71 * item_width, 0.6625 * item_height},
    p7_ {0.29 * item_width, 0.9875 * item_height},
    p8_ {0.71 * item_width, 0.9875 * item_height};

    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);

    painter->drawLine(p1_,p2_);
    painter->drawLine(p2_,p4_);
    painter->drawLine(p4_,p3_);
    painter->drawLine(p4_,p6_);
    painter->drawLine(p6_,p5_);
    painter->drawLine(p6_,p8_);
    painter->drawLine(p8_,p7_);

    fixed_item::paint(painter, option, widget);
}

}
