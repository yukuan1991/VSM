#include "board_arrival.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {

///修改成item_width * 1/4
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
    item_width_ /= width_heigth_small_;
    item_height_ /=width_heigth_small_;

}

void board_arrival::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    std::array<QPointF, 5> polygon_shape
    {
        QPointF{0.3 * item_width_, 0.3 * item_height_},
        QPointF{0.6375 * item_width_, 0.3 * item_height_},
        QPointF{0.7 * item_width_, 0.3625 * item_height_},
        QPointF{0.7 * item_width_, 0.675 * item_height_},
        QPointF{0.3 * item_width_, 0.675 * item_height_}
    };

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(std::max(item_width_ * 0.02, 2.0));
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);

    painter->drawPolygon(polygon_shape.data(), polygon_shape.size(), Qt::WindingFill);

    for (auto&& it : polygon_shape)
    {
        it += QPointF (-0.1 * item_width_, 0.1 * item_height_);
    }
    painter->drawPolygon(polygon_shape.data(), polygon_shape.size(), Qt::WindingFill);

    for (auto&& it : polygon_shape)
    {
        it += QPointF (-0.1 * item_width_, 0.1 * item_height_);
    }
    painter->drawPolygon(polygon_shape.data(), polygon_shape.size(), Qt::WindingFill);

    item::paint(painter, option, widget);
}
}
