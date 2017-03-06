#pragma once
#include "item/abstract_item.h"
#include "item/arrow_item.h"
#include <QFont>



namespace item {

class fifo : public arrow_item
{
public:
    static unique_ptr<fifo> make (json data, QPointF pos, abstract_item* parent = nullptr);
    bool init ();
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    fifo (json data, QPointF pos, abstract_item* parent = nullptr);
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
private:
    QPointF begin_, end_;
    qreal angle_, length_;
    QFont font_;
    qreal font_width_, font_height_;
    QPainterPath shape_;
    QRectF bounding_rect_;
    static constexpr qreal tip_length = 5;
    static constexpr qreal thickness = 20;

};

} // namespace item

