#include "balanced_production.h"
///修改好了
namespace item {


std::unique_ptr<balanced_production> balanced_production::make(nlohmann::json data, QPointF pos, item *parent)
{
    std::unique_ptr<balanced_production>ret(new balanced_production (::move (data), pos, parent));
    if (!ret->init ())
    {
        return nullptr;
    }
    else
    {
        return ret;
    }
}

bool balanced_production::init()
{
    set_item_type("均衡生产");

    set_attribute ("生产品类");
    set_attribute ("生产数量");

    set_z_value(317);

    return true;
}

balanced_production::balanced_production(nlohmann::json data, QPointF pos, item* parent)
    :fixed_item(::move (data), pos, parent)
{

}

void balanced_production::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width_);
    painter->setPen(the_pen);

    QRectF rect (0.05 * item_width_, 0.25 * item_height_, 0.9 * item_width_, 0.5 * item_height_);

    auto font = painter->font();
    font.setBold(true);
    font.setPointSize (12);
    QFontMetricsF metrics (font);
    auto w = metrics.width("O X O X");
    auto h = metrics.height();

    auto center = rect.center();
    auto text_rect = QRectF (center.x() - 0.5 * w, center.y() - 0.5 * h, w, h);

    painter->setBrush(Qt::white);
    painter->drawRect(rect);

    painter->setFont(font);
    painter->drawText(text_rect,"O X O X", Qt::AlignVCenter | Qt::AlignCenter);

    item::paint(painter, option, widget);
}
}
