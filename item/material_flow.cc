#include "material_flow.h"
#include "qt-tools/graphics.hpp"
#include <QtMath>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

namespace item {


std::unique_ptr<material_flow> material_flow::make(QPointF start, QPointF end, QColor color, item *parent)
{
    std::unique_ptr<material_flow> ret (new material_flow (start, end, ::move (color), parent));

    if (!ret->init())
    {
        return nullptr;
    }

    return ret;
}

material_flow::~material_flow()
{

}

material_flow::material_flow(QPointF p1, QPointF p2, QColor color, item *parent)
    :item (parent)
{
    auto mid_pos = (p1 + p2) / 2;
    setPos(mid_pos);
    start_ = p1 - mid_pos;
    end_ = p2 - mid_pos;
    set_color(::move (color));
    set_z_value(201);
}

bool material_flow::init()
{
    constexpr auto min_distance = head_ratio * width;
    auto p1 = start_, p2 = end_;

    if (distance(p1, p2) <= min_distance)
    {
        return false;
    }

    arrow_tip_ = p2;

    QLineF line (p1, p2);
    auto body_end_p = line.pointAt((line.length() - min_distance) / line.length());
    QLineF line_body (p1, body_end_p);

    auto top_angle = line_body.angle() + 90;
    auto x_diff = -qCos (qDegreesToRadians (top_angle)) * width;
    auto y_diff = qSin (qDegreesToRadians (top_angle)) * width;

    auto start = line_body.p1();
    auto end = line_body.p2();

    body_p1_ = QPointF {start.x() + x_diff, start.y() + y_diff};
    body_p2_ = QPointF {end.x() + x_diff, end.y() + y_diff};
    body_p3_ = QPointF {start.x() - x_diff, start.y() - y_diff};
    body_p4_ = QPointF {end.x() - x_diff, end.y() - y_diff};

    QLineF head_line {body_p2_, body_p4_};
    neck1_ = head_line.pointAt(-0.5);
    neck2_ = head_line.pointAt(1.5);


    /// 初始化边框信息
    auto outer_start = line_body.pointAt (-outer_gap / line_body.length());

    auto outer_x_diff = -qCos (qDegreesToRadians (top_angle)) * (width + outer_gap);
    auto outer_y_diff = qSin (qDegreesToRadians (top_angle)) * (width + outer_gap);

    auto line_outer = QLineF (outer_start,
                              line_body.pointAt((line_body.length() - outer_gap) / line_body.length()));
    auto outer_end = line_outer.p2();

    outer_p1_ = QPointF {outer_start.x() + outer_x_diff, outer_start.y() + outer_y_diff};
    outer_p2_ = QPointF {outer_end.x() + outer_x_diff, outer_end.y() + outer_y_diff};
    outer_p3_ = QPointF {outer_start.x() - outer_x_diff, outer_start.y() - outer_y_diff};
    outer_p4_ = QPointF {outer_end.x() - outer_x_diff, outer_end.y() - outer_y_diff};

    QLineF arrow_normal (body_end_p, arrow_tip_);
    QLineF arrow_side1 (body_end_p, neck1_);
    QLineF arrow_slope1 (arrow_tip_, neck1_);

    auto tip_diff = outer_gap * (arrow_slope1.length() / arrow_side1.length());
    outer_tip_ = arrow_normal.pointAt((arrow_normal.length() + tip_diff) / arrow_normal.length());

    QLineF tmp_side1_outer = arrow_side1.translated(outer_end - body_end_p);
    QLineF tmp_slope1_outer = arrow_slope1.translated(outer_tip_ - arrow_tip_);

    tmp_side1_outer.intersect(tmp_slope1_outer, & (outer_neck1_));

    if (outer_neck1_.isNull())
    {
        return false;
    }

    outer_neck2_ = QLineF (outer_end, outer_neck1_).pointAt(-1);
    return true;
}

void material_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QPen pen;
    pen.setColor(color ());
    painter->setPen(pen);

    painter->drawLine(body_p1_, body_p2_);
    painter->drawLine(body_p2_, body_p4_);
    painter->drawLine(body_p4_, body_p3_);
    painter->drawLine(body_p3_, body_p1_);

    QLineF line1 {body_p1_, body_p2_};
    QLineF line2 {body_p3_, body_p4_};

    auto rate = fill_distance * 2 / line1.length();
    decltype (rate) fill_step = 0;
    painter->setBrush(color ());
    bool color_or_white = false;

    painter->save();
    while (fill_step < 1)
    {
        color_or_white = !color_or_white;
        painter->setBrush(color_or_white ? color () : Qt::white);
        auto end_paint = fill_step + rate;

        auto p1_fill = line1.pointAt(fill_step);
        auto p2_fill = line1.pointAt(end_paint > 1 ? 1 : end_paint);
        auto p3_fill = line2.pointAt(fill_step);
        auto p4_fill = line2.pointAt(end_paint > 1 ? 1 : end_paint);

        painter->drawPolygon ({{p1_fill, p2_fill, p4_fill, p3_fill}}, Qt::WindingFill);
        fill_step += (rate);
    }

    painter->restore();
    painter->drawPolygon({{neck1_, neck2_, arrow_tip_}}, Qt::WindingFill);
    if (option->state bitand QStyle::State_Selected)
    {
        painter->setPen(Qt::DashLine);
        painter->setBrush(Qt::transparent);

        QPainterPath path;
        path.moveTo(outer_p4_);
        path.lineTo(outer_p3_);
        path.lineTo(outer_p1_);
        path.lineTo(outer_p2_);
        path.lineTo(outer_neck1_);
        path.lineTo(outer_tip_);
        path.lineTo(outer_neck2_);
        path.lineTo(outer_p4_);
        painter->drawPath(path);
    }
}

QRectF material_flow::boundingRect() const
{
    return QPolygonF {{body_p1_, body_p2_, neck1_, arrow_tip_, neck2_, body_p4_, body_p3_}}.boundingRect();
}

QPainterPath material_flow::shape() const
{
    QPainterPath path;
    path.addPolygon({{outer_p1_, outer_p2_, outer_neck1_, outer_tip_,
                      outer_neck2_, outer_p4_, outer_p3_}});
    path.lineTo(outer_p1_);
    return path;
}

} // namespace item
