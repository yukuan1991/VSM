#include "rectangles.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<production_sequence>production_sequence::make(QPointF pos, QColor color)
{
    std::unique_ptr <production_sequence> ret(new production_sequence);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

production_sequence::production_sequence(item* parent)
    :item(parent)
{

}

void production_sequence::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "wecome paint";
     Q_UNUSED(widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(the_pen);
    painter->drawPolygon({{p1, p2, p4, p3}},Qt::WindingFill);
    painter->drawLine(p5,p6);
   item::paint(painter, option, widget);
  }
}
