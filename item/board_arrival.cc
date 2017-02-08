#include "board_arrival.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<board_arrival> board_arrival::make(QPointF pos, QColor color)
{
    std::unique_ptr <board_arrival> ret(new board_arrival);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "看板以批量方式传达";
    return ret;
}

board_arrival::board_arrival(item* parent)
    :item(parent)
{
    set_attribute ("生产批量");

}

void board_arrival::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
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
    the_pen.setWidthF(item_width / 50);
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

    item::paint(painter, option, widget);
}
}
