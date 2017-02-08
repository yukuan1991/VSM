#include "fifo.h"
#include <QLineF>
#include <QPainter>
#include <QFontMetricsF>

namespace item {

std::unique_ptr<fifo> fifo::make(QPointF pos, QColor color)
{
    auto ret = std::unique_ptr<fifo> (new fifo);

    if (ret == nullptr)
    {
        return nullptr;
    }

    ret->setPos(pos);
    ret->set_color(::move (color));

    return ret;
}

fifo::fifo(item *parent)
    :item (parent)
{

}

void fifo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(item_width_ * 0.02);
    painter->setPen(the_pen);

    const QLineF
            top_line (0.05 * item_width_, item_height_ / 3, 0.95 * item_width_, item_height_ / 3),
            bottom_line (0.05 * item_width_, item_height_ / 3 * 2, 0.95 * item_width_, item_height_ / 3 * 2);

    /// Set Bold
    auto font = painter->font();
    font.setBold(true);
    painter->setFont(font);

    /// Mesure font size
    QFontMetricsF metrics (painter->font());
    auto font_width = metrics.width("FIFO");
    auto font_height = metrics.height();
    auto mid_point = QPointF (item_width_ / 2, item_height_ / 2);

    auto text_rect = QRectF (mid_point - QPointF {font_width / 2, font_height / 2},
                             QSizeF {font_width, font_height});

    painter->drawLine(top_line);
    painter->drawLine(bottom_line);
    painter->drawLine(QPointF (0.05 * item_width_, item_height_ / 2),
                      QPointF (text_rect.left() - 0.05 * item_width_, item_height_ / 2));


    painter->drawText(text_rect, "FIFO", Qt::AlignHCenter | Qt::AlignVCenter);
    painter->drawLine(QPointF (text_rect.right() + 0.05 * item_width_, item_height_ / 2),
                      QPointF (0.9 * item_width_, item_height_ / 2));


    QPointF top_tip (0.9 * item_width_, item_height_ / 2 + item_height_ * 2 / 80);
    QPointF bottom_tip (0.9 * item_width_, item_height_ / 2 - item_height_ * 2 / 80);
    QPointF mid_tip (0.95 * item_width_, item_height_ / 2);

    the_pen.setWidthF(0.01 * item_width_);
    painter->setPen(the_pen);

    painter->setBrush(Qt::black);
    painter->drawPolygon({{top_tip, bottom_tip, mid_tip}}, Qt::WindingFill);

    item::paint (painter, option, widget);
}


} // namespace item
