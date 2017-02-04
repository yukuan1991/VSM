#include "storage_super_market.h"
#include <memory>
#include <QDebug>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
///修改好
namespace item {


std::unique_ptr<storage_super_market> storage_super_market::make(QPointF pos, QColor color)
{
    std::unique_ptr <storage_super_market> ret(new storage_super_market);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "库存超市";
    return ret;
}

storage_super_market::storage_super_market(item* parent)
    :item(parent)
{

}

void storage_super_market::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);

    painter->drawLine(p1_,p2_);
    painter->drawLine(p2_,p4_);
    painter->drawLine(p4_,p3_);
    painter->drawLine(p4_,p6_);
    painter->drawLine(p6_,p5_);
    painter->drawLine(p6_,p8_);
    painter->drawLine(p8_,p7_);

    item::paint(painter, option, widget);
}

}
