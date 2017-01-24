#include "convey.h"
#include <memory>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<convey> convey::make(QPointF pos, QColor color)
{
    std::unique_ptr <convey> ret(new convey);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

convey::convey(item* parent)
    :item (parent)
{

}

void convey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    painter->setPen(the_pen);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawArc(x,y,width,heigth,startAngle,spanAngle);
    painter->drawEllipse(35.0, 40.0, 30.0, 30.0);
    item::paint(painter, option, widget);

  }

}
