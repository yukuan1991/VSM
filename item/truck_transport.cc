#include "truck_transport.h"
#include "QPainter"
#include "QStyleOptionGraphicsItem"
namespace item {


std::unique_ptr<truck_transport> truck_transport::make( json data, QPointF pos,item* parent)
{

    std::unique_ptr<truck_transport>ret(new truck_transport(::move(data), pos, parent));

    if(!ret->init ())
    {
        return nullptr;
    }
    else
    {

    return ret;
    }
}

truck_transport::truck_transport(json data, QPointF pos, item * parent)
    :fixed_item(::move(data), pos, parent)
{

}

bool truck_transport::init()
{
    set_attribute("运输频率");

    set_z_value(305);

    set_item_type("卡车运输");

    return true;
}

void truck_transport::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width_);
    painter->setPen(the_pen);

    auto x_scale = width() / 100;
    auto y_scale = height() / 80;

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

