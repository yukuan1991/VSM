#include "item/board_info_flow.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include "qt-tools/graphics.hpp"
//namespace item {
//
//
//unique_ptr<board_info_flow> board_info_flow::make(vector<unique_ptr<QGraphicsLineItem> > tmp_lines, QColor color, item *parent)
//{
//    unique_ptr <board_info_flow> ret (new board_info_flow (parent));
//
//    if (! ret->init(::move (tmp_lines)))
//    {
//        return nullptr;
//    }
//    return ret;
//}
//
//board_info_flow::board_info_flow(item* parent)
//    :item(parent)
//{
//    set_z_value(103);
//}
//
//bool board_info_flow::init(vector<unique_ptr<QGraphicsLineItem> > tmp_lines)
//{
//    set_item_type("看板用信息流");
//    if (tmp_lines.empty ())
//    {
//        return false;
//    }
//
//    auto begin_ptr = tmp_lines.front()->line().p1();
//    setPos(begin_ptr);
//    lines_.reserve(tmp_lines.size ());
//    for (auto & it : tmp_lines)
//    {
//        if (it->line().length() > 1)
//        {
//            lines_.emplace_back (it->line().p1() - begin_ptr, it->line().p2() - begin_ptr);
//        }
//    }
//
//    for (auto  & it : lines_)
//    {
//        nlohmann::json line_data;
//        line_data ["x1"] = it.x1();
//        line_data ["x2"] = it.x2();
//        line_data ["y1"] = it.y1();
//        line_data ["y2"] = it.y2();
//        item_info_["lines"].push_back(::move (line_data));
//    }
//
//    return true;
//}
//
//void board_info_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    Q_UNUSED (widget);
//    auto lines = this->lines_;
//    if (lines.empty())
//    {
//        return;
//    }
//
//    QPen pen;
//    pen.setWidthF(2.0);
//    pen.setColor (Qt::black);
//
//    painter->setBrush(Qt::black);
//    if (option->state bitand QStyle::State_Selected)
//    {
//        pen.setColor(Qt::red);
//        painter->setBrush (Qt::red);
//    }
//    pen.setStyle(Qt::DashLine);
//    painter->setPen(pen);
//
//
//    auto last_line = lines.back ();
//    lines.pop_back ();
//
//    for (auto & it : lines)
//    {
//        painter->drawLine (it);
//    }
//
//    auto arrow_length = last_line.length ();
//    auto body_length = arrow_length - tip_length;
//    auto body_end = QLineF {last_line.p1(), last_line.p2 ()}.pointAt(body_length / arrow_length);
//    auto vertical_line = QLineF (body_end, last_line.p1 ()).normalVector();
//
//    auto neck1 = vertical_line.pointAt(tip_width / vertical_line.length());
//    auto neck2 = vertical_line.pointAt(- tip_width / vertical_line.length());
//
//
//    painter->drawLine(last_line.p1 (), body_end);
//    pen.setWidthF(1);
//    pen.setStyle(Qt::SolidLine);
//    painter->setPen (pen);
//    painter->drawPolygon({{neck1, neck2, last_line.p2 ()}}, Qt::WindingFill);
//}
//
//QRectF board_info_flow::boundingRect() const
//{
//    return {-20, -20, 40, 40};
//}
//
//}
//

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

    painter->drawLines (lines_.data (), static_cast<ssize_t> (lines_.size ()));
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
