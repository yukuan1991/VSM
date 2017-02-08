#include "board_station.h"
#include <memory>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
///修改完成
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

    const QPointF p1 {0.2 * item_width_, 0.125 * item_height_},
    p2 {0.8 * item_width_, 0.125 * item_height_},
    p3 {0.25 * item_width_, 0.5 * item_height_},
    p4 {0.5 * item_width_, 0.5 * item_height_},
    p5 {0.75 * item_width_, 0.5 * item_height_},
    p6 {0.25 *item_width_, 0.875 * item_height_},
    p7 {0.5 * item_width_, 0.875 * item_height_},
    p8 {0.75 * item_width_, 0.875 * item_height_};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(item_width_ / 50);
    painter->setPen(the_pen);

    ///给定坐标
    painter->drawLine(p1,p3);
    painter->drawLine(p3,p5);
    painter->drawLine(p5,p2);
    painter->drawLine(p4,p7);
    painter->drawLine(p6,p8);
    item::paint(painter, option, widget);
}

board_station::board_station(item* parent)
    :item(parent)
{

}
}
