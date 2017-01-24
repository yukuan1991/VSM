#include "round.h"
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QPainterPath>
namespace item {


std::unique_ptr<round> round::make(QPointF pos, QColor color)
{

    std::unique_ptr <round> ret(new round);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

round::round(item* parent)
    :item(parent)
{

}

void round::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(Qt::black);
    painter->drawEllipse(0.1 * item_width, 10.0, 60.0, 60.0);
    painter->drawEllipse(25.0, 25.0, 30.0, 30.0);
    item::paint(painter, option, widget);
  }
}
