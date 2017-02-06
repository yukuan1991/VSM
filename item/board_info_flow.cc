#include "board_info_flow.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<board_info_flow> board_info_flow::make(QPointF pos, QColor color)
{
    std::unique_ptr <board_info_flow> ret (new board_info_flow);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "看板用流信息";
    return ret;
}

board_info_flow::board_info_flow(item* parent)
    :item(parent)
{

}

void board_info_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget);

    QPointF
    p1 {0.3 * item_width, 0.25 * item_height},
    p2 {0.7 * item_width, 0.25 * item_height},
    p3 {0.3 * item_width, 0.625 * item_height},
    p4 {0.25 * item_width, 0.625 * item_height},
    p5 {0.35 * item_width, 0.625 * item_height},
    p6 {0.3 * item_width, 0.6875 * item_height};

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
