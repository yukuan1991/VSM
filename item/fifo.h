#pragma once
#include "item/item.h"
#include <QFont>


namespace item {

class fifo : public item
{
public:
    static std::unique_ptr<fifo> make(QPointF begin, QPointF end, QColor = Qt::black, item* parent = nullptr);
    bool init ();
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    fifo (QPointF begin, QPointF end, QColor color, item* parent = nullptr);
private:
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
    QPointF begin_, end_;
    qreal angle_, length_;
    QFont font_;
    qreal font_width_, font_height_;
    QPainterPath shape_;
    QRectF bounding_rect_;
    static constexpr qreal tip_length_ratio = 1.0 / 100.0 * 5.0;

};

} // namespace item

