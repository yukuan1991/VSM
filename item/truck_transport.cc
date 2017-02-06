#include "truck_transport.h"
#include "QPainter"
#include "QStyleOptionGraphicsItem"
namespace item {


std::unique_ptr<truck_transport> truck_transport::make(QPointF pos, QColor color)
{

    std::unique_ptr<truck_transport>ret(new truck_transport);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "卡车运输";
    return ret;
}

truck_transport::truck_transport(item * parent)
    :item(parent)
{

}

void truck_transport::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width);
    painter->setPen(the_pen);

    auto x_scale = item_width / 100;
    auto y_scale = item_height / 80;

    painter->setBrush(Qt::white);

    QVector<QPointF> polygon_shape
    {
        {x_scale * 1, y_scale * 1},
        {x_scale * 69, y_scale * 1},
        {x_scale * 69, y_scale * 55},
        {x_scale * 1, y_scale * 55}
    };
    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    polygon_shape.clear();
    polygon_shape = {
        {x_scale * 69, y_scale * 25},
        {x_scale * 99, y_scale * 25},
        {x_scale * 99, y_scale * 55},
        {x_scale * 69, y_scale * 55}
    };
    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    painter->setBrush(Qt::black);
    painter->drawEllipse (QPointF {x_scale * 17, y_scale * 65}, x_scale * 12, x_scale * 12);
    painter->drawEllipse (QPointF {x_scale * 72, y_scale * 65}, x_scale * 12, x_scale * 12);

    item::paint(painter, option, widget);


}


}

