#include "board_station.h"
#include <memory>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
///修改完成
namespace item {

bool board_station::init()
{
     set_item_type("看板站");
     set_z_value(311);
     return true;
}

std::unique_ptr<board_station> board_station::make(json data, QPointF pos, item* parent)
{
    std::unique_ptr <board_station> ret(new board_station(::move(data), pos, parent));
    if( !ret->init ())
    {
        return nullptr;
    }
    else
    {
         return ret;
    }

}

void board_station::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto item_width = width();
    auto item_height = height();

    const QPointF p1 {0.2 * item_width, 0.125 * item_height},
    p2 {0.8 * item_width, 0.125 * item_height},
    p3 {0.25 * item_width, 0.5 * item_height},
    p4 {0.5 * item_width, 0.5 * item_height},
    p5 {0.75 * item_width, 0.5 * item_height},
    p6 {0.25 *item_width, 0.875 * item_height},
    p7 {0.5 * item_width, 0.875 * item_height},
    p8 {0.75 * item_width, 0.875 * item_height};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(item_width / 50);
    painter->setPen(the_pen);

    ///给定坐标
    painter->drawLine(p1,p3);
    painter->drawLine(p3,p5);
    painter->drawLine(p5,p2);
    painter->drawLine(p4,p7);
    painter->drawLine(p6,p8);
    fixed_item::paint(painter, option, widget);
}

board_station::board_station(json data, QPointF pos,item* parent)
    :fixed_item(::move(data), pos, parent)
{


}
}
