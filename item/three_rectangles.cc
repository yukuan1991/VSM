#include "three_rectangles.h"
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

namespace item {


three_rectangles::three_rectangles(item* parent)
    :item (parent)
{

}

void three_rectangles::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "wecome paint";
     Q_UNUSED(widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(the_pen);
    painter->drawPolygon({{p1, p2, p4, p3}},Qt::WindingFill);
    painter->drawLine(p5,p6);
    painter->drawLine(p7,p8);
    painter->drawLine(p9,p10);
    if (option->state bitand QStyle::State_Selected)
    {
        qDebug()<<"长方形被选中";
        painter->setBrush(Qt::transparent);
        QPen pen;
        pen.setColor(Qt::black);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }


}

std::unique_ptr<three_rectangles> three_rectangles::make(QPointF pos, QColor color)
{
    std::unique_ptr<three_rectangles> ret(new three_rectangles);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
 }
}
