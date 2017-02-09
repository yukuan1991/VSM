﻿#include "sequence_pull_ball.h"
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QPainterPath>
///修改好
/// 修改成1/4
namespace item {


std::unique_ptr<sequence_pull_ball> sequence_pull_ball::make(QPointF pos, QColor color)
{
    std::unique_ptr <sequence_pull_ball> ret(new sequence_pull_ball);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "顺序拉动球";
    return ret;
}

sequence_pull_ball::sequence_pull_ball(item* parent)
    :item(parent)
{
    item_width_ /= small_object_ratio;
    item_height_ /= small_object_ratio;

    set_z_value(310);
}

void sequence_pull_ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    auto x_scale = item_width_ * 0.01;
    auto y_scale = item_height_ / 80;

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidthF (std::max (x_scale * 2.0, 2.0));
    painter->setPen(the_pen);
    painter->drawEllipse(QRectF {20 * x_scale, 10 * y_scale, 60 * x_scale, 60 * y_scale});
    painter->drawEllipse(QRectF {35 * x_scale, 25 * y_scale, 30 * x_scale, 30 * y_scale});

    item::paint(painter, option, widget);
}
}
