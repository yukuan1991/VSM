#include "balanced_production.h"

namespace item {


std::unique_ptr<balanced_production> balanced_production::make(QPointF pos, QColor color)
{
    std::unique_ptr<balanced_production>ret(new balanced_production);
    ret->setPos(pos);
    ret->set_color( std::move (color));
    return ret;
}

balanced_production::balanced_production(item* parent)
    :item(parent)
{

}

void balanced_production::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width);
    painter->setPen(the_pen);

    QRectF rect (0.05 * item_width, 0.25 * item_height, 0.9 * item_width, 0.5 * item_height);

    QFontMetricsF metrics (painter->font());

    auto font_width = metrics.width("OXOX");
    auto font_height = metrics.height();
    auto center = rect.center();
    auto text_rect = QRectF (center.x() - 0.5 * font_width, center.y() - 0.5 * font_height, font_width, font_height);

    painter->drawRect(rect);
    painter->drawText(text_rect,"OXOX", Qt::AlignVCenter | Qt::AlignCenter);

    item::paint(painter, option, widget);
}
}
