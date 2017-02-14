#include "value_added_radtio.h"
#include <QPainter>
namespace item {


value_added_radtio::value_added_radtio(item* parent)
    :item(parent)
{

}

void value_added_radtio::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto x_scale = item_width_ / 100;
    auto y_scale = item_height_ / 80;

    QPointF p1{1 * x_scale, 1 * y_scale},
    p2{124 * x_scale, 1 * y_scale},
    p3{1 * x_scale, 40 * y_scale},
    p4{124 * x_scale, 40 * y_scale},
    p5{1 * x_scale, 79 * y_scale},
    p6{124 * x_scale, 79 * y_scale};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(std::max(item_width_ * 0.02,2.0));
    painter->setBrush(Qt::white);
    painter->setPen(the_pen);
    painter->drawPolygon({{p1,p2,p5,p6}},Qt::WindingFill);
    painter->drawLine(p3,p4);

    item::paint(painter,option,widget);

}

std::unique_ptr<value_added_radtio> value_added_radtio::make(QPointF pos, QColor color)
{
    std::unique_ptr<value_added_radtio> ret(new value_added_radtio);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "增值比";
    return ret;
}
}
