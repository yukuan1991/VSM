#include "item/fifo.h"
#include <QLineF>
#include <QPainter>
#include <QFontMetricsF>
#include <QDebug>
#include <QPolygonF>
#include <QStyleOptionGraphicsItem>

namespace item {

unique_ptr<fifo> fifo::make(json data, QPointF pos, abstract_item *parent)
{
    auto ret = unique_ptr<fifo> (new fifo (::move (data), pos, parent));

    if (ret == nullptr or ! ret->init ())
    {
        return nullptr;
    }

    return ret;
}

bool fifo::init()
{
    if (arrow_item::init () == false)
    {
        return false;
    }

    font_.setPointSizeF (12);
    font_.setBold (true);
    QFontMetricsF metrics (font_);
    font_width_ = metrics.width("FIFO");
    font_height_ = metrics.height ();

    if (radius() * 2 < font_width_ + tip_length + 10 + 10)
    {
        return false;
    }

    const auto rect = QRectF (- radius(), - thickness / 2, radius () * 2, thickness);
    const auto matrix = [angle = angle ()] () { QMatrix m; m.rotate (- angle); return m; } ();
    const auto polygon = QPolygonF (rect);
    const auto mapped_polygon = matrix.map(polygon);

    shape_.addPolygon(mapped_polygon);
    bounding_rect_ = shape_.boundingRect();

    return true;
}

void fifo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);
    const QColor color = option->state bitand QStyle::State_Selected ? selected_color() : Qt::black;

    {
        auto pen = painter->pen ();
        pen.setColor(color);
        pen.setWidthF(2.0);
        painter->setPen(pen);
    }

    painter->setFont (font_);

    {
        painter->save();
        SCOPE_EXIT { painter->restore (); };
        painter->rotate(- angle ());

        painter->setBrush(color);
        painter->drawLine(QPointF (start_pos ().x(), thickness / 2), QPointF (stop_pos ().x(), thickness / 2));
        painter->drawLine(QPointF (start_pos ().x(), - thickness / 2), QPointF (stop_pos ().x(), - thickness / 2));
        painter->drawLine (start_pos (), QPointF (- font_width_ / 2 - 10, 0));
        painter->drawLine (QPointF (font_width_ / 2 + 10, 0), QPointF (stop_pos().x() - tip_length, 0));
        const auto tip_p1 = QPointF (stop_pos ().x () - tip_length, 2);
        const auto tip_p2 = QPointF (stop_pos ().x () - tip_length, - 2);

        {
            painter->save();
            SCOPE_EXIT { painter->restore (); };
            if (p1 ().x () > p2 ().x())
            {
                painter->rotate (180);
            }

            painter->drawText(QRectF (- font_width_ / 2, - font_height_ / 2, font_width_, font_height_), "FIFO");
        }
        {
            painter->save();
            SCOPE_EXIT { painter->restore (); };

            auto pen = painter->pen ();
            pen.setWidthF (1.0);
            painter->setPen (pen);

            painter->drawPolygon ({{tip_p1, tip_p2, stop_pos ()}}, Qt::WindingFill);
        }
    }
}

fifo::fifo(json data, QPointF pos, abstract_item *parent)
    :arrow_item (::move (data), pos, parent)
{

}

QRectF fifo::boundingRect() const
{
    return bounding_rect_;
}

QPainterPath fifo::shape() const
{
    return shape_;
}

}
