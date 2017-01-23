﻿#include "information.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<information> information::make(QPointF pos, QColor color)
{
    std::unique_ptr <information> ret (new information);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

information::information(item* parent)
    :item(parent)
{

}

void information::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    qDebug() << "wecome paint";
     Q_UNUSED(widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(color());
    the_pen.setStyle(Qt::DashLine);
    the_pen.setBrush(Qt::black);
    painter->setPen(the_pen);
    painter->drawLine(p1,p2);
    painter->drawLine(p1,p3);

    the_pen.setStyle(Qt::SolidLine);
    painter->drawLine(p4,p5);
    painter->drawLine(p5,p6);
    painter->drawLine(p6,p4);


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