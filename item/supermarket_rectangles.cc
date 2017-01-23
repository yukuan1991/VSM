#include "supermarket_rectangles.h"
#include <memory>
#include <QDebug>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<supermarket_rectangles> supermarket_rectangles::make(QPointF pos, QColor color)
{
    std::unique_ptr <supermarket_rectangles> ret(new supermarket_rectangles);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

supermarket_rectangles::supermarket_rectangles(item* parent)
    :item(parent)
{

}

void supermarket_rectangles::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "wecome paint";
     Q_UNUSED(widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(the_pen);
    //painter->drawPolygon({{p1,p2,p4,p3}});

    painter->drawLine(p1,p2);
    painter->drawLine(p2,p4);
    painter->drawLine(p4,p3);
    painter->drawLine(p4,p6);
    painter->drawLine(p6,p5);
    painter->drawLine(p6,p8);
    painter->drawLine(p8,p7);
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

}
