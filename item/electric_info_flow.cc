#include "electric_info_flow.h"
#include "qt-tools/graphics.hpp"
#include <QPainter>
#include <QDebug>
#include <QStyleOptionGraphicsItem>

namespace item {

std::unique_ptr<electric_info_flow> electric_info_flow::make(QPointF p1, QPointF p2, QColor color, item *parent)
{
    auto ret = std::unique_ptr<electric_info_flow> (new electric_info_flow (p1, p2, parent, color));
    if (!ret->init())
    {
        return nullptr;
    }
    return ret;
}

electric_info_flow::~electric_info_flow()
{

}

electric_info_flow::electric_info_flow(QPointF p1, QPointF p2, item *parent, QColor color)
    :item (parent)
{
    auto mid_pos = (p1 + p2) / 2;
    setPos((p1 + p2) / 2);
    start_ = p1 - mid_pos;
    end_ = p2 - mid_pos;
    set_color(::move (color));
    type_ = "电子信息流";

    set_z_value(102);
}

bool electric_info_flow::init()
{
    auto dist = distance(start_, end_);
    if (dist < 3 * width)
    {
        return false;
    }

    auto normal = QLineF (QLineF (start_, end_).pointAt(0.5), end_).normalVector();
    QPointF side_p1 = normal.pointAt(width / normal.length());
    QPointF side_p2 = normal.pointAt(-width / normal.length());
    mid_p1_ = QLineF ((start_ + end_) / 2, end_).translated(side_p1 - (start_ + end_) / 2).unitVector().pointAt(width);
    mid_p2_ = QLineF ((start_ + end_) / 2, start_).translated(side_p2 - (start_ + end_) / 2).unitVector().pointAt(width);

    QLineF end_line (mid_p2_, end_);
    if (QLineF (mid_p2_, end_).length() < tip_length)
    {
        return false;
    }

    body_end_ = end_line.pointAt((end_line.length() - tip_length) / end_line.length());
    neck1_ = QLineF (body_end_, mid_p2_).normalVector().unitVector().pointAt(tip_width);
    neck2_ = QLineF (body_end_, mid_p2_).normalVector().unitVector().pointAt(-tip_width);

    item_info_["begin"]["x"] = start_.x();
    item_info_["begin"]["y"] = start_.y();
    item_info_["end"]["x"] = end_.x();
    item_info_["end"]["y"] = end_.y();

    return true;
}

void electric_info_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);
    QPen pen;
    pen.setWidthF (2.0);
    pen.setColor (color ());

    if (option->state bitand QStyle::State_Selected)
    {
        pen.setColor(Qt::red);
    }

    painter->setPen(pen);

    painter->drawLine(start_, mid_p1_);

    painter->drawLine(mid_p1_, mid_p2_);
    painter->drawLine(mid_p2_, body_end_);

    painter->setBrush(color ());
    painter->drawPolygon({{neck1_, neck2_, end_}}, Qt::WindingFill);
}

QRectF electric_info_flow::boundingRect() const
{
    return QPolygonF {{start_, mid_p1_, end_, mid_p2_}}.boundingRect();
}

QPainterPath electric_info_flow::shape() const
{
    QPainterPath path;
    path.addPolygon({{start_, mid_p1_, end_, mid_p2_}});
    path.lineTo(start_);
    return path;
}

} // namespace item
