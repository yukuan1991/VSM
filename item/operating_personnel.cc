#include "operating_personnel.h"
#include <memory>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
///修改好
/// 修改好1/4
namespace item
{

std::unique_ptr<operating_personnel> operating_personnel::make(QPointF pos, QColor color)
{
    std::unique_ptr<operating_personnel> ret(new operating_personnel);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "操作员";
    return ret;
}

operating_personnel::operating_personnel(item* parent)
    :fixed_item (parent)
{
    set_attribute("操作员数量");

    set_z_value(309);

    item_width_ /= small_object_ratio;
    item_height_ /= small_object_ratio;

}

void operating_personnel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(std::max(0.02 * item_width_,2.0));
    painter->setPen(the_pen);

    painter->drawArc(QRectF{0.1 * item_width_, item_height_ * 10 / 80, 0.8 * item_width_, item_height_ * 60 / 80}, 180 * 16, 180 * 16);
    painter->setBrush(Qt::white);
    painter->drawEllipse (QRectF(0.3 * item_width_, item_height_ * 20 / 80, 0.4 * item_width_, item_height_ * 40 / 80));

    item::paint(painter, option, widget);
}
}
