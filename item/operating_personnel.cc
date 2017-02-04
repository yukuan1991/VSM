#include "operating_personnel.h"
#include <memory>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
namespace item
{

std::unique_ptr<operating_personnel> operating_personnel::make(QPointF pos, QColor color)
{
    std::unique_ptr<operating_personnel> ret(new operating_personnel);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

operating_personnel::operating_personnel(item* parent)
    :item (parent)
{

}

void operating_personnel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width);
    painter->setPen(the_pen);

    painter->drawArc(QRectF{0.1 * item_width, item_height * 10 / 80, 0.8 * item_width, item_height * 60 / 80}, 180 * 16, 180 * 16);
    painter->setBrush(Qt::white);
    painter->drawEllipse (QRectF(0.3 * item_width, item_height * 20 / 80, 0.4 * item_width, item_height * 40 / 80));
    item::paint(painter, option, widget);
}
}
