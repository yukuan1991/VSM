#include "fetch_material.h"
#include <QPointF>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QRectF>
///取料

namespace item {

std::unique_ptr<fetch_material> fetch_material::make(json data, QPointF pos, item* parent)
{
    std::unique_ptr<fetch_material>ret(new fetch_material(::move(data), pos, parent));
    if(! ret->init ())
    {
        return nullptr;
    }
    else
    {

        return ret;
    }
}

bool fetch_material::init()
{
    set_item_type("取料");
    set_z_value(203);

    return true;
}

fetch_material::fetch_material(json data, QPointF pos, item *parent)
    :fixed_item(::move(data), pos, parent)
{


}

void fetch_material::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto item_width = width();
    auto item_height = height();
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(std::max(item_width * 0.02, 2.0));
    painter->setPen(the_pen);

    QPointF
    p1 {0.75 * item_width, 0.76 * item_height},
    p2 {0.82 * item_width, 0.9 * item_height},
    p3 {0.86 * item_width,0.65 * item_height};

    //给定坐标
    painter->setBrush(Qt::white);

    painter->drawArc(QRectF{0.1 * item_width, 0, 0.8 * item_width, item_height}, 45 * 16, 270 * 16);
    painter->setBrush(Qt::black);
    painter->drawPolygon({{p1,p2,p3}},Qt::WindingFill);

    //fixed_item::paint(painter, option, widget);
}

}
