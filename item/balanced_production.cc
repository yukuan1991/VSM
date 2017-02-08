#include "balanced_production.h"
///修改好了
namespace item {


std::unique_ptr<balanced_production> balanced_production::make(QPointF pos, QColor color)
{
    std::unique_ptr<balanced_production>ret(new balanced_production);
    ret->setPos(pos);
    ret->set_color( std::move (color));
    ret->type_ = "均衡生产";
    return ret;
}

balanced_production::balanced_production(item* parent)
    :item(parent)
{
    set_attribute ("生产品类");
    set_attribute ("生产数量");

    set_z_value(12);

}

void balanced_production::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width_);
    painter->setPen(the_pen);

    QRectF rect (0.05 * item_width_, 0.25 * item_height_, 0.9 * item_width_, 0.5 * item_height_);


    QFontMetricsF metrics (painter->font());
    auto w = metrics.width("O X O X");
    auto h = metrics.height();

    auto center = rect.center();
    auto text_rect = QRectF (center.x() - 0.5 * w, center.y() - 0.5 * h, w, h);

    painter->drawRect(rect);
    painter->drawText(text_rect,"O X O X", Qt::AlignVCenter | Qt::AlignCenter);
    item::paint(painter, option, widget);
}
}
