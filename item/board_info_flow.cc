#include "item/board_info_flow.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include "qt-tools/graphics.hpp"

namespace item {

unique_ptr<board_info_flow> board_info_flow::make(json data, QPointF pos, abstract_item *parent)
{
    auto ret = unique_ptr<board_info_flow> (new board_info_flow (::move (data), pos, parent));
    if (ret == nullptr or ! ret->init ())
    {
        return nullptr;
    }

    return ret;
}

board_info_flow::board_info_flow(nlohmann::json data, QPointF pos, abstract_item *parent)
    :abstract_item (::move (data), pos, parent)
{

}

bool board_info_flow::init() try
{
    auto json_lines = json_find (dump (), "lines");

    decltype (lines_) lines;

    decltype (shape_) shape;

    for (auto & it : json_lines)
    {
        const qreal x1 = json_find (it, "x1");
        const qreal x2 = json_find (it, "x2");
        const qreal y1 = json_find (it, "y1");
        const qreal y2 = json_find (it, "y2");

        const auto p1 = QPointF (x1, y1);
        const auto p2 = QPointF (x2, y2);

        const auto current_pos = pos ();

        const auto relative_p1 = p1 - current_pos;
        const auto relative_p2 = p2 - current_pos;
        shape.addPolygon (get_line_polygon (QLineF (relative_p1, relative_p2), 10.0));

        lines.emplace_back (relative_p1, relative_p2);
    }

    if (lines.empty ())
    {
        return false;
    }

    bounding_rect_ = shape.boundingRect ();
    shape_ = ::move (shape);
    lines_ = ::move (lines);

    return true;
}
catch (const std::exception &)
{
    return false;
}

void board_info_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);
    const QColor color = option->state bitand QStyle::State_Selected ? selected_color () : Qt::black;

    auto pen = painter->pen ();
    pen.setStyle (Qt::DashLine);
    pen.setWidthF (2.0);
    pen.setColor (color);
    painter->setPen (pen);
    assert (!lines_.empty ());
    painter->setBrush (color);

    painter->drawLines (lines_.data (), static_cast<ssize_t> (lines_.size ()));
    const auto & last_line = lines_.back ();

    const auto last_len = last_line.length ();
    const auto body_end = last_line.pointAt((last_len - tip_length) / last_len);
    const auto side_p1 = QLineF (body_end,  last_line.p2 ()).normalVector().unitVector().pointAt(tip_width);
    const auto side_p2 = QLineF (body_end, last_line.p2 ()).normalVector().unitVector().pointAt(- tip_width);

    painter->drawPolygon ({{side_p1, side_p2, last_line.p2 ()}}, Qt::WindingFill);
}

QRectF board_info_flow::boundingRect() const
{
    return bounding_rect_;
}

QPainterPath board_info_flow::shape() const
{
    return shape_;
}

}
