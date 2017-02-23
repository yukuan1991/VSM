#include "board_arrival.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {

///修改成item_width * 1/4
bool board_arrival::init()
{
   set_item_type("看板以批量方式传达");
   set_attribute ("生产批量");

   set_z_value(316);

   return true;

}

std::unique_ptr<board_arrival> board_arrival::make(json data, QPointF pos, item* parent)
{
    std::unique_ptr <board_arrival> ret(new board_arrival (::move(data), pos, parent));

    if(!ret->init ())
    {
        return nullptr;
    }
    else
    {
        return ret;
    }
}

board_arrival::board_arrival(json data, QPointF pos, item* parent)
    :fixed_item(::move(data), pos, parent)
{

}

void board_arrival::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto item_width = width ();
    auto item_height = width ();
    std::array<QPointF, 5> polygon_shape
    {
        QPointF{0.3 * item_width, 0.3 * item_height},
        QPointF{0.6375 * item_width, 0.3 * item_height},
        QPointF{0.7 * item_width, 0.3625 * item_height},
        QPointF{0.7 * item_width, 0.675 * item_height},
        QPointF{0.3 * item_width, 0.675 * item_height}
    };

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);

    painter->drawPolygon(polygon_shape.data(), polygon_shape.size(), Qt::WindingFill);

    for (auto&& it : polygon_shape)
    {
        it += QPointF (-0.1 * item_width, 0.1 * item_height);
    }
    painter->drawPolygon(polygon_shape.data(), polygon_shape.size(), Qt::WindingFill);

    for (auto&& it : polygon_shape)
    {
        it += QPointF (-0.1 * item_width, 0.1 * item_height);
    }
    painter->drawPolygon(polygon_shape.data(), polygon_shape.size(), Qt::WindingFill);

    fixed_item::paint(painter, option, widget);
}
}
