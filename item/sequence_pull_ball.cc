#include "sequence_pull_ball.h"
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
    item_width_ /= width_heigth_small_;
    item_height_ /= width_heigth_small_;

}

void sequence_pull_ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidth(item_width_ * 0.02);
    painter->setPen(the_pen);
    painter->drawEllipse(QRectF {0.2 * item_width_, item_height_ / 8, 0.6 * item_width_, 60 * item_height_ / 80});
    painter->drawEllipse(QRectF {0.35 * item_width_, 25.0 *item_height_ / 80, 30.0, 30.0});

    item::paint(painter, option, widget);
}
}
