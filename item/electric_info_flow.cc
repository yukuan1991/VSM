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
    ,p1_ (p1)
    ,p2_ (p2)
{
    set_color(::move (color));
}

bool electric_info_flow::init()
{
    auto dist = distance(p1_, p2_);
    if (dist < 3 * width)
    {
        return false;
    }

    auto normal = QLineF (QLineF (p1_, p2_).pointAt(0.5), p2_).normalVector();
    QPointF side_p1 = normal.pointAt(width / normal.length());
    QPointF side_p2 = normal.pointAt(-width / normal.length());
    mid_p1_ = QLineF ((p1_ + p2_) / 2, p2_).translated(side_p1 - (p1_ + p2_) / 2).unitVector().pointAt(width);
    mid_p2_ = QLineF ((p1_ + p2_) / 2, p1_).translated(side_p2 - (p1_ + p2_) / 2).unitVector().pointAt(width);

    QLineF end_line (mid_p2_, p2_);
    if (QLineF (mid_p2_, p2_).length() < tip_length)
    {
        return false;
    }

    body_end_ = end_line.pointAt( (end_line.length() - tip_length) / end_line.length());
    neck1_ = QLineF (body_end_, mid_p2_).normalVector().unitVector().pointAt(tip_width);
    neck2_ = QLineF (body_end_, mid_p2_).normalVector().unitVector().pointAt(-tip_width);


    return true;
}

void electric_info_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);
    QPen pen;
    pen.setWidthF (2.0);
    painter->setPen(pen);

    painter->drawLine(p1_, mid_p1_);

    painter->drawLine(mid_p1_, mid_p2_);
    painter->drawLine(mid_p2_, body_end_);

    painter->setBrush(color ());
    painter->drawPolygon({{neck1_, neck2_, p2_}}, Qt::WindingFill);

    if (option->state bitand QStyle::State_Selected)
    {
        qDebug () << "selected" << dynamic_cast<QObject*> (this);
    }
}

QRectF electric_info_flow::boundingRect() const
{
    return QPolygonF {{p1_, mid_p1_, p2_, mid_p2_}}.boundingRect();
}

QPainterPath electric_info_flow::shape() const
{
    return item::shape();
}

} // namespace item
