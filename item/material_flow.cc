#include "material_flow.h"
#include "qt-tools/graphics.hpp"
#include <QtMath>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace item {


unique_ptr<item> material_flow::make(nlohmann::json data, QPointF pos, item *parent)
{
    std::unique_ptr<material_flow> ret (new material_flow (::move (data), pos, parent));

    if (!ret->init())
    {
        return nullptr;
    }

    return ret;
}

material_flow::~material_flow()
{

}

material_flow::material_flow(nlohmann::json data, QPointF pos, item *parent)
    :arrow_item (::move (data), pos, parent)
{

}

bool material_flow::init()
{
    if (!arrow_item::init ())
    {
        return false;
    }

    if (distance (p1 (), p2 ()) < head_distance)
    {
        return false;
    }
    set_item_type("物流");

    const auto line = QLineF (p1 (), p2 ());
    auto angle = line.angle ();
    const auto length = line.length();
    const auto straight_line = QLineF (QPointF (- length / 2, 0), QPointF (length / 2, 0));
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

    const auto matrix = [angle] () { QMatrix m; m.rotate (- angle); return m; } ();

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
    angle_ = angle;


    return true;
}

void material_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    const QColor fore_color (option->state bitand QStyle::State_Selected ? Qt::red : Qt::black);

    auto body_start_x = body_p1_.x ();
    auto body_end_x = body_p2_.x ();

    {
        painter->save();
        SCOPE_EXIT { painter->restore(); };
        painter->setPen (fore_color);
        painter->setBrush (Qt::white);

        painter->rotate(- angle_);
        painter->drawPolygon({{body_p1_, body_p2_, body_neck1_, arrow_tip_, body_neck2_, body_p3_, body_p4_}},
                             Qt::WindingFill);

        auto rect_top_left = QPointF (body_start_x, - width);
        const auto increment = fill_distance * 2;

        painter->setBrush(fore_color);

        while (rect_top_left.x() < body_end_x)
        {
            auto distance = body_end_x - rect_top_left.x();
            auto rect_size = QSizeF (std::min (distance, increment / 2), 2 * width);
            painter->drawRect(QRectF (rect_top_left, rect_size));

            rect_top_left += QPointF (increment, 0);

        }
    }


    //QPen pen;
    //pen.setColor(Qt::black);
    //painter->setPen(pen);

    //painter->drawLine(body_p1_, body_p2_);
    //painter->drawLine(body_p2_, body_p4_);
    //painter->drawLine(body_p4_, body_p3_);
    //painter->drawLine(body_p3_, body_p1_);

    //QLineF line1 {body_p1_, body_p2_};
    //QLineF line2 {body_p3_, body_p4_};

    //auto rate = fill_distance * 2 / line1.length();
    //decltype (rate) fill_step = 0;
    //painter->setBrush(Qt::black);
    //bool color_or_white = false;

    //painter->save();
    //while (fill_step < 1)
    //{
    //    color_or_white = !color_or_white;
    //    painter->setBrush(color_or_white ? Qt::black : Qt::white);
    //    auto end_paint = fill_step + rate;

    //    auto p1_fill = line1.pointAt(fill_step);
    //    auto p2_fill = line1.pointAt(end_paint > 1 ? 1 : end_paint);
    //    auto p3_fill = line2.pointAt(fill_step);
    //    auto p4_fill = line2.pointAt(end_paint > 1 ? 1 : end_paint);

    //    painter->drawPolygon ({{p1_fill, p2_fill, p4_fill, p3_fill}}, Qt::WindingFill);
    //    fill_step += (rate);
    //}

    //painter->restore();
    //painter->drawPolygon({{neck1_, neck2_, arrow_tip_}}, Qt::WindingFill);
    //if ((option->state bitand QStyle::State_Selected) and show_frame ())
    //{
    //    painter->setPen(Qt::DashLine);
    //    painter->setBrush(Qt::transparent);

    //    QPainterPath path;
    //    path.moveTo(outer_p4_);
    //    path.lineTo(outer_p3_);
    //    path.lineTo(outer_p1_);
    //    path.lineTo(outer_p2_);
    //    path.lineTo(outer_neck1_);
    //    path.lineTo(outer_tip_);
    //    path.lineTo(outer_neck2_);
    //    path.lineTo(outer_p4_);
    //    painter->drawPath(path);
    //}
}

QRectF material_flow::boundingRect() const
{
    return bounding_rect_;
}

QPainterPath material_flow::shape() const
{
    return shape_;
}

} // namespace item
