#include "production_sequence.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
///修改完成
namespace item {


std::unique_ptr<production_sequence>production_sequence::make(QPointF pos, QColor color)
{
    std::unique_ptr <production_sequence> ret(new production_sequence);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "生产工序";
    return ret;
}

production_sequence::production_sequence(item* parent)
    :item(parent)
{

}

void production_sequence::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget);

    QPointF
    p1_ {0.01 * item_width, 0.0125 * item_height},
    p2_ {0.99 * item_width, 0.0125 * item_height},
    p3_ {0.01 * item_width, 0.35 * item_height},
    p4_ {0.99 * item_width, 0.35 * item_height},
    p5_ {0.01 * item_width, 0.9875 * item_height},
    p6_ {0.99 * item_width, 0.9875 * item_height};


    auto the_pen = painter->pen ();
    the_pen.setBrush(Qt::white);
    the_pen.setColor(color ());
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);
    painter->drawPolygon({{p1_, p2_, p6_, p5_}},Qt::WindingFill);
    painter->drawLine(p3_,p4_);

   item::paint(painter, option, widget);
  }
}
