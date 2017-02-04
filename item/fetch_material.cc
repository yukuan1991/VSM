﻿#include "fetch_material.h"
#include <QPointF>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QRectF>
///取料

namespace item {

std::unique_ptr<fetch_material> fetch_material::make(QPointF pos, QColor color)
{
    std::unique_ptr<fetch_material>ret(new fetch_material);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

fetch_material::fetch_material(item *parent)
    :item(parent)
{

}

void fetch_material::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    //给定坐标
    painter->setBrush(Qt::white);

    painter->drawArc(QRectF{0.1 * item_width, 0, 0.8 * item_width, item_height}, 45 * 16, 270 * 16);
    painter->setBrush(Qt::black);
    painter->drawPolygon({{p1,p2,p3}},Qt::WindingFill);

    item::paint(painter, option, widget);
}

}