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

}

void board_arrival::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto polygon_shape = polygon_shape_;

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(item_width / 50);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);

    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    for (auto&& it : polygon_shape)
    {
        it += QPointF (-0.1 * item_width, 0.1 * item_height);
    }
    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    for (auto&& it : polygon_shape)
    {
        it += QPointF (-0.1 * item_width, 0.1 * item_height);
    }
    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    item::paint(painter, option, widget);
}
}
