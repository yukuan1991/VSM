﻿#include "product_to_customer.h"

namespace item {

std::unique_ptr<product_to_customer> product_to_customer::make(QPointF p1, QPointF p2, QColor color, item *parent)
{
    auto ret = unique_ptr<product_to_customer> (new product_to_customer (p1, p2, parent, ::move (color)));
    if (!ret->init())
    {
        return nullptr;
    }
    ret->type_ = "传统信息流";
    return ret;

}

product_to_customer::~product_to_customer()
{

}

product_to_customer::product_to_customer(QPointF p1, QPointF p2, item *parent, QColor color)
{

}

bool product_to_customer::init()
{
    return true;
}

void product_to_customer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

QRectF product_to_customer::boundingRect() const
{
    return {};
}

QPainterPath product_to_customer::shape() const
{
    return {};
}


} // namespace item