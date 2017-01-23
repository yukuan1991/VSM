#include "board.h"
#include <memory>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<board> board::make(QPointF pos, QColor color)
{
    std::unique_ptr <board> ret(new board);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

void board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    painter->setPen(the_pen);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawLine(p1,p3);
    painter->drawLine(p3,p5);
    painter->drawLine(p5,p2);
    painter->drawLine(p4,p7);
    painter->drawLine(p6,p8);

    item::paint(painter, option, widget);
}

board::board(item* parent)
    :item(parent)
{

 }
}
