#include "product_to_customer.h"
#include "qt-tools/graphics.hpp"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace item {

unique_ptr<product_to_customer> product_to_customer::make(json data, QPointF pos, abstract_item *parent)
{
    auto ret = unique_ptr<product_to_customer> (new product_to_customer (::move (data), pos, parent));
    if (ret == nullptr or ! ret->init ())
    {
        return nullptr;
    }

    return ret;
}

product_to_customer::~product_to_customer()
{

}

product_to_customer::product_to_customer(nlohmann::json data, QPointF pos, abstract_item *parent)
    :arrow_item (::move (data), pos, parent)
{

}

bool product_to_customer::init()
{
    if (!arrow_item::init ())
    {
        return false;
    }

    if (distance (p1 (), p2 ()) < head_distance)
    {
        return false;
    }
    set_item_type("成品发送至顾客");

    const auto straight_line = QLineF (start_pos (), stop_pos ());
    const auto body_end_x = straight_line.p2 ().x () - head_distance;
    const auto body_start_x = straight_line.p1().x();

    const auto body_p1 = QPointF (body_start_x, width);
    const auto body_p2 = QPointF (body_end_x, width);
    const auto body_p3 = QPointF (body_end_x, - width);
    const auto body_p4 = QPointF (body_start_x, - width);

    auto neck_diff = QPointF (0, width / 2);
    const auto body_neck1 = body_p2 + neck_diff;
    const auto body_neck2 = body_p3 - neck_diff;
    const auto arrow_tip = straight_line.p2 ();

    const auto matrix = [angle = angle ()] () { QMatrix m; m.rotate (- angle); return m; } ();

    QPainterPath path;
    path.moveTo (body_p1);

    for (auto it : {body_p1, body_p2,body_neck1, arrow_tip, body_neck2, body_p3, body_p4})
    {
        path.lineTo (it);
    }
    path.lineTo (body_p1);

    shape_ = matrix.map(path);
    bounding_rect_ = shape_.boundingRect();

    body_p1_ = body_p1;
    body_p2_ = body_p2;
    body_p3_ = body_p3;
    body_p4_ = body_p4;
    body_neck1_ = body_neck1;
    body_neck2_ = body_neck2;
    arrow_tip_ = arrow_tip;


    return true;

}

void product_to_customer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    const QColor fore_color (option->state bitand QStyle::State_Selected ? selected_color () : Qt::black);

    {
        painter->save();
        SCOPE_EXIT { painter->restore(); };
        painter->setPen (fore_color);
        painter->setBrush (Qt::white);

        painter->rotate(- angle ());
        painter->drawPolygon({{body_p1_, body_p2_, body_neck1_, arrow_tip_, body_neck2_, body_p3_, body_p4_}},
                             Qt::WindingFill);
    }

}

QRectF product_to_customer::boundingRect() const
{
    return bounding_rect_;
}

QPainterPath product_to_customer::shape() const
{
    return shape_;
}

}
