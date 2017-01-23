
#include "triangle.h"
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

namespace item {


triangle::triangle(item *parent)
    :item (parent)
{

}

void triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "wecome paint";
     Q_UNUSED(widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(the_pen);
    painter->drawLine(p1,p2);
    painter->drawLine(p1,p3);
    painter->drawLine(p2,p3);
    if (option->state bitand QStyle::State_Selected)
    {
        painter->setBrush(Qt::transparent);
        QPen pen;
        pen.setColor(Qt::black);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }

}

std::unique_ptr<triangle> triangle::make(QPointF pos, QColor color)
{
    std::unique_ptr <triangle> ret (new triangle);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;

}
}
