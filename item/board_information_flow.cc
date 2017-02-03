#include "board_information_flow.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<board_information_flow> board_information_flow::make(QPointF pos, QColor color)
{
    std::unique_ptr <board_information_flow> ret (new board_information_flow);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

board_information_flow::board_information_flow(item* parent)
    :item(parent)
{

}

void board_information_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
  //  painter->drawPolygon({{p6,p4,p5,p3}},Qt::WindingFill);
    painter->drawLine(p4,p5);
    painter->drawLine(p5,p6);
    painter->drawLine(p6,p4);
    item::paint(painter, option, widget);
   }
}
