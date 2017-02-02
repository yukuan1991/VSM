#include "sequence_pull_ball.h"
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QPainterPath>
namespace item {


std::unique_ptr<sequence_pull_ball> sequence_pull_ball::make(QPointF pos, QColor color)
{
    std::unique_ptr <sequence_pull_ball> ret(new sequence_pull_ball);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

sequence_pull_ball::sequence_pull_ball(item* parent)
    :item(parent)
{

}

void sequence_pull_ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(Qt::black);
    painter->drawEllipse(QRectF {0.2 * item_width, item_height / 8, 0.6 * item_width, 60 * item_height / 80});
    painter->drawEllipse(QRectF {0.35 * item_width, 25.0 *item_height / 80, 30.0, 30.0});

    item::paint(painter, option, widget);
}
}
