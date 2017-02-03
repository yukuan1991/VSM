#include "storage_super_market.h"
#include <memory>
#include <QDebug>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<storage_super_market> storage_super_market::make(QPointF pos, QColor color)
{
    std::unique_ptr <storage_super_market> ret(new storage_super_market);
    ret->setPos(pos);
    ret->set_color(std::move(color));
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
    painter->setPen(the_pen);
    painter->drawLine(p1,p2);
    painter->drawLine(p2,p4);
    painter->drawLine(p4,p3);
    painter->drawLine(p4,p6);
    painter->drawLine(p6,p5);
    painter->drawLine(p6,p8);
    painter->drawLine(p8,p7);
    item::paint(painter, option, widget);
  }

}
