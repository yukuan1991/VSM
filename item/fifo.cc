#include "fifo.h"
#include <QLineF>
#include <QPainter>
#include <QFontMetricsF>
#include <QDebug>

namespace item {

std::unique_ptr<fifo> fifo::make(QPointF begin, QPointF end, QColor color, item *parent)
{
    auto ret = std::unique_ptr<fifo> (new fifo (begin, end, color, parent));

    if (ret == nullptr or !ret->init ())
    {
        return nullptr;
    }

    return ret;
}

bool fifo::init()
{
    QLineF line (begin_, end_);
    auto angle = line.angle();
    auto length = line.length();
    angle_ = angle;
    length_ = length;

    font_.setPointSizeF (item_height_ / 16 * 2.5);
    font_.setBold (true);
    QFontMetrics metrics (font_);
    font_width_ = metrics.width("FIFO");
    font_height_ = metrics.height ();

    shape_.moveTo (QPointF (- length_ / 2, - item_height_ / 8));
    shape_.lineTo (QPointF (length_ / 2, - item_height_ / 8));
    shape_.lineTo (QPointF (length_ / 2, item_height_ / 8));
    shape_.lineTo (QPointF (- length_ / 2, item_height_ / 8));
    shape_.lineTo(QPointF (- length_ / 2, - item_height_ / 8));

    QMatrix matrix;
    matrix.rotate (- angle_);
    shape_ = matrix.map (shape_);
    bounding_rect_ = shape_.boundingRect();

    if (length_ < font_width_ + item_width_ * tip_length_ratio)
    {
        return false;
    }

    return true;
}


void fifo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);
    auto font = painter->font ();
    painter->setFont (font_);
    auto x_scale = item_width_ / 100;
    auto y_scale = item_height_ / 80;

    {
        painter->save ();
        SCOPE_EXIT { painter->restore (); };
        painter->rotate (- angle_);

        painter->drawLine(QPointF (- length_ / 2, 10 * y_scale), QPointF (length_ / 2, 10 * y_scale));
        painter->drawLine(QPointF (- length_ / 2, 0), QPointF (- font_width_ / 2, 0));
        auto tip_start_x = length_ / 2 - (item_width_ * tip_length_ratio);

        painter->drawLine(QPointF (font_width_ / 2, 0), QPointF (tip_start_x, 0));
        {
            painter->save ();
            SCOPE_EXIT { painter->restore (); };

            painter->setBrush(Qt::black);
            the_pen.setWidthF(1.0);
            painter->setPen (the_pen);
            painter->drawPolygon({{QPointF (tip_start_x, 2 * y_scale),
                                   QPointF (tip_start_x, - 2 * y_scale),
                                   QPointF (length_ / 2, 0)}}, Qt::WindingFill);
        }

        painter->drawLine(QPointF (- length_ / 2, - item_height_ / 8), QPointF (length_ / 2, - item_height_ / 8));
        {
            painter->save ();
            SCOPE_EXIT { painter->restore (); };
            if (begin_.x() > end_.x ())
            {
                painter->rotate (180);
            }
            painter->drawText(QRectF (QPointF (- font_width_ / 2, - font_height_ / 2),
                                      QSizeF (font_width_, font_height_)), "FIFO");
            painter->setFont(font);
            paint_attribute(painter);
        }
    }


}

fifo::fifo(QPointF begin, QPointF end, QColor color, item *parent)
    :item (parent)
    ,begin_ (::move (begin))
    ,end_ (::move (end))
{
    auto mid_point = (begin_ + end_) / 2;
    begin_ -= mid_point;
    end_ -= mid_point;
    setPos (mid_point);
    set_attribute("最大批量");

    set_color(::move (color));

    set_z_value(204);

}

QRectF fifo::shape_rect() const
{
    return QRectF (QPointF (- length_ / 2,  - item_height_ / 8),
                   QSizeF (length_, item_height_ / 4));
}

QRectF fifo::boundingRect() const
{
    return bounding_rect_;
}

QPainterPath fifo::shape() const
{
    return shape_;
}


} // namespace item
