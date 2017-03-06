#include <QDebug>
#include "item/traditional_info_flow.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "qt-tools/graphics.hpp"
#include <QPolygonF>

namespace item {

unique_ptr<traditional_info_flow> traditional_info_flow::make(json data, QPointF pos, abstract_item *parent)
{
    auto ret = unique_ptr<traditional_info_flow> (new traditional_info_flow (::move (data), pos, parent));
    if (ret == nullptr or ! ret->init ())
    {
        return nullptr;
    }

    return ret;
}

traditional_info_flow::~traditional_info_flow()
{

}

traditional_info_flow::traditional_info_flow(nlohmann::json data, QPointF pos, abstract_item *parent)
    :arrow_item (::move (data), pos, parent)
{

}

bool traditional_info_flow::init()
{
    if (!arrow_item::init())
    {
        return false;
    }

    if (::distance (p1 (), p2 ()) < tip_length)
    {
        return false;
    }

    set_item_type("传统信息流");

    const auto rect = QRectF (start_pos().x(), - tip_width, 2 * radius (), 2 * tip_width);

    const auto matrix = [angle = angle ()] () { QMatrix m; m.rotate (- angle); return m; } ();
    const auto polygon = QPolygonF (rect);
    const auto mapped_polygon = matrix.map(polygon);


    shape_.addPolygon(mapped_polygon);
    bounding_rect_ = shape_.boundingRect ();

    return true;
}

void traditional_info_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);

    const QColor color = option->state bitand QStyle::State_Selected ? selected_color() : Qt::blue;
    {
        auto pen = painter->pen();
        pen.setColor(color);
        pen.setWidthF(2.0);
        painter->setPen(pen);
    }


    const auto r = radius();

    const auto straight_line = QLineF (start_pos (), stop_pos ());

    const auto body_begin_pos = start_pos ();
    const auto body_end_pos = straight_line.pointAt((r * 2 - 10) / (r * 2));
    const auto body_line = QLineF (body_begin_pos, body_end_pos);

    const auto arrow_upper_tip = QPointF (body_end_pos.x(), tip_width);
    const auto arrow_lower_tip = QPointF (body_end_pos.x(), - tip_width);
    const auto arrow_end_tip = stop_pos ();



    {
        painter->save();
        SCOPE_EXIT { painter->restore(); };

        painter->rotate(- angle ());
        painter->drawLine (body_line);
        {
            painter->save();
            SCOPE_EXIT { painter->restore(); };

            painter->setBrush(color);
            painter->drawPolygon({{arrow_upper_tip, arrow_lower_tip, arrow_end_tip}}, Qt::WindingFill);
        }
    }
}

QRectF traditional_info_flow::boundingRect() const
{
    return bounding_rect_;
}

QPainterPath traditional_info_flow::shape() const
{
    return shape_;
}

} /// end of namespace item
