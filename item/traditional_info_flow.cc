#include "traditional_info_flow.h"
#include "qt-tools/graphics.hpp"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QtMath>

namespace item {


std::unique_ptr<traditional_info_flow> traditional_info_flow::make(QPointF p1, QPointF p2, QColor color, item *parent)
{
    auto ret = std::unique_ptr<traditional_info_flow> (new traditional_info_flow (p1, p2, parent, ::move (color)));
    if (!ret->init())
    {
        return nullptr;
    }
    ret->type_ = "传统信息流";
    return ret;
}

traditional_info_flow::~traditional_info_flow()
{

}

traditional_info_flow::traditional_info_flow(QPointF p1, QPointF p2, item *parent, QColor color)
    :item (parent)
{
    auto mid = (p1 + p2) / 2;
    setPos(mid);
    start_ = p1 - mid;
    end_ = p2 - mid;

    set_z_value(8);

    set_color(::move (color));
}

bool traditional_info_flow::init()
{
    auto arrow_length = distance (start_, end_);
    if (arrow_length < tip_length)
    {
        return false;
    }

    auto body_length = arrow_length - tip_length;
    body_end_ = QLineF {start_, end_}.pointAt(body_length / arrow_length);
    auto vertical_line = QLineF (body_end_, start_).normalVector();

    neck1_ = vertical_line.pointAt(tip_width / vertical_line.length());
    neck2_ = vertical_line.pointAt(- tip_width / vertical_line.length());

    auto top_angle = QLineF (start_, body_end_).angle() + 90;

    auto x_diff = -qCos (qDegreesToRadians (top_angle)) * bound_width;
    auto y_diff = qSin (qDegreesToRadians (top_angle)) * bound_width;

    outer_p1_ = {start_.x() + x_diff, start_.y() + y_diff};
    outer_p2_ = {body_end_.x() + x_diff, body_end_.y() + y_diff};
    outer_p3_ = {start_.x() - x_diff, start_.y() - y_diff};
    outer_p4_ = {body_end_.x() - x_diff, body_end_.y() - y_diff};


    return true;
}

void traditional_info_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QPen pen;
    pen.setColor(color ());
    pen.setWidthF(2.0);
    painter->setPen(pen);

    painter->drawLine(start_, body_end_);
    painter->setBrush(color ());
    pen.setWidthF(1);
    painter->drawPolygon({{neck1_, neck2_, end_}}, Qt::WindingFill);
    if (option->state bitand QStyle::State_Selected)
    {
        set_dash(painter);
        painter->drawPath(shape ());
    }

}

QRectF traditional_info_flow::boundingRect() const
{
    return QPolygonF {{start_, neck1_, end_, neck2_}}.boundingRect();
}

QPainterPath traditional_info_flow::shape() const
{
    QPainterPath path;
    path.moveTo(outer_p1_);
    path.lineTo(outer_p2_);
    path.lineTo(outer_p4_);
    path.lineTo(outer_p3_);
    path.lineTo(outer_p1_);
    return path;
}

} // namespace item
