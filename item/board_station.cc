#include "board_station.h"
#include <memory>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

namespace item {

std::unique_ptr<board_station> board_station::make(QPointF pos, QColor color)
{
    std::unique_ptr <board_station> ret(new board_station);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "看板站";
    return ret;
}

void board_station::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    const QPointF p1_ {0.2 * item_width, 0.125 * item_height};
    const QPointF p2_ {0.8 * item_width, 0.125 * item_height};
    const QPointF p3_ {0.25 * item_width, 0.5 * item_height};
    const QPointF p4_ {0.5 * item_width, 0.5 * item_height};
    const QPointF p5_ {0.75 * item_width, 0.5 * item_height};
    const QPointF p6_ {0.25 * item_width, 0.875 * item_height};
    const QPointF p7_ {0.5 * item_width, 0.875 * item_height};
    const QPointF p8_ {0.75 * item_width, 0.875 * item_height};

    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);


    painter->drawLine(p1_,p3_);
    painter->drawLine(p3_,p5_);
    painter->drawLine(p5_,p2_);
    painter->drawLine(p4_,p7_);
    painter->drawLine(p6_,p8_);

    item::paint(painter, option, widget);
}

board_station::board_station(item* parent)
    :item(parent)
{

}
}
