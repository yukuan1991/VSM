#pragma once
#include "item/item.h"
#include "utility/memory.hpp"


namespace item {


class product_to_customer : public item
{
public:
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    static unique_ptr<product_to_customer> make (QPointF p1, QPointF p2, QColor color = Qt::black,
                                                item* parent = nullptr);
    ~product_to_customer () override;

protected:
    explicit product_to_customer (QPointF p1, QPointF p2, item* parent = nullptr, QColor color = Qt::black);
    bool init ();

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
private:
    QPointF start_, end_;
    QPointF body_end_, neck1_, neck2_;
    QPointF outer_p1_, outer_p2_, outer_neck1_, outer_tip_, outer_neck2_, outer_p4_, outer_p3_;
    constexpr static qreal tip_width = 3;
    constexpr static qreal tip_length = 10;
    constexpr static qreal bound_width = 5;
};

} // namespace item
