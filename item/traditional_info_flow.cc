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
    return ret;
}

traditional_info_flow::~traditional_info_flow()
{

}

traditional_info_flow::traditional_info_flow(QPointF p1, QPointF p2, item *parent, QColor color)
    :item (parent)
    , p1_ (p1)
    , p2_ (p2)
{
    set_color(::move (color));
}

bool traditional_info_flow::init()
{
    auto arrow_length = distance (p1_, p2_);
    if (arrow_length < tip_length)
    {
        return false;
    }

    auto body_length = arrow_length - tip_length;
    body_end_ = QLineF {p1_, p2_}.pointAt(body_length / arrow_length);
    auto vertical_line = QLineF (body_end_, p1_).normalVector();

    neck1_ = vertical_line.pointAt(tip_width / vertical_line.length());
    neck2_ = vertical_line.pointAt(- tip_width / vertical_line.length());

    auto top_angle = QLineF (p1_, body_end_).angle() + 90;

    auto x_diff = -qCos (qDegreesToRadians (top_angle)) * bound_width;
    auto y_diff = qSin (qDegreesToRadians (top_angle)) * bound_width;

    outer_p1_ = {p1_.x() + x_diff, p1_.y() + y_diff};
    outer_p2_ = {body_end_.x() + x_diff, body_end_.y() + y_diff};
    outer_p3_ = {p1_.x() - x_diff, p1_.y() - y_diff};
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

    painter->drawLine(p1_, body_end_);
    painter->setBrush(color ());
    pen.setWidthF(1);
    painter->drawPolygon({{neck1_, neck2_, p2_}}, Qt::WindingFill);
    if (option->state bitand QStyle::State_Selected)
    {
        set_dash(painter);
        painter->drawPath(shape ());
    }

}

QRectF traditional_info_flow::boundingRect() const
{
    return QPolygonF {{p1_, neck1_, p2_, neck2_}}.boundingRect();
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
