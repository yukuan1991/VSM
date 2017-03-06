#include "electric_info_flow.h"
#include "qt-tools/graphics.hpp"
#include <QPainter>
#include <QDebug>
#include <QStyleOptionGraphicsItem>

namespace item {

unique_ptr<electric_info_flow> electric_info_flow::make(json data, QPointF pos, abstract_item *parent)
{
    auto ret = unique_ptr<electric_info_flow> (new electric_info_flow (::move (data), pos, parent));
    if (ret == nullptr or ! ret->init ())
    {
        return nullptr;
    }
    return ret;
}

electric_info_flow::~electric_info_flow()
{

}

electric_info_flow::electric_info_flow(json data, QPointF pos, abstract_item *parent)
    :arrow_item (::move (data), pos, parent)
{

}

bool electric_info_flow::init()
{
    if (!arrow_item::init())
    {
        return false;
    }

    if (::distance (p1 (), p2 ()) < 3 * width)
    {
        return false;
    }

    set_item_type("电子信息流");

    const auto mid_p1 = QPointF (width / 2, width);
    const auto mid_p2 = QPointF (- width / 2, - width);

    const auto matrix = [angle = angle ()] () { QMatrix m; m.rotate (- angle); return m; } ();
    const auto polygon = QPolygonF {{start_pos (), mid_p1, stop_pos (), mid_p2}};
    const auto mapped_polygon = matrix.map(polygon);


    shape_.addPolygon(mapped_polygon);
    bounding_rect_ = shape_.boundingRect ();
    mid_p1_ = mid_p1;
    mid_p2_ = mid_p2;

    return true;
}

void electric_info_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);
    QColor color = option->state bitand QStyle::State_Selected ? selected_color () : Qt::blue;

    {
        auto pen = painter->pen ();
        pen.setColor (color);
        pen.setWidthF (2.0);

        painter->setPen (pen);
    }

    {
        painter->save ();
        SCOPE_EXIT { painter->restore (); };

        painter->rotate (- angle ());
        const auto last_line = QLineF (mid_p2_, stop_pos ());
        painter->drawLines({QLineF (start_pos (), mid_p1_),
                            QLineF (mid_p1_, mid_p2_),
                            last_line});

        const auto last_len = last_line.length ();
        const auto body_end = last_line.pointAt((last_len - width) / last_len);
        const auto side_p1 = QLineF (body_end, stop_pos ()).normalVector().unitVector().pointAt(tip_width);
        const auto side_p2 = QLineF (body_end, stop_pos ()).normalVector().unitVector().pointAt(- tip_width);

        {
            painter->save ();
            SCOPE_EXIT { painter->restore (); };
            painter->setBrush(color);
            painter->drawPolygon ({{side_p1, side_p2, stop_pos ()}}, Qt::WindingFill);
        }
    }

}

QRectF electric_info_flow::boundingRect() const
{
    return bounding_rect_;
}

QPainterPath electric_info_flow::shape() const
{
    return shape_;
}

}
