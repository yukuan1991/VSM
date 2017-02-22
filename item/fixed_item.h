#pragma once
#include "item/item.h"


namespace item {

class fixed_item : public item
{
public:
    virtual void paint_attribute (QPainter* painter);
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
protected:
    explicit fixed_item (item *parent = 0);
    explicit fixed_item (json data, QPointF pos, item* parent);
    void set_dash(QPainter *painter);
    constexpr static qreal standard_width () { return standard_width_; }
    constexpr static qreal standard_height () { return standard_height_; }
    QRectF boundingRect () const override;

    virtual qreal width () const { return standard_width(); }
    virtual qreal height () const { return standard_height(); }
protected:
    static constexpr qreal standard_width_ = 100;
    static constexpr qreal standard_height_ = 80;
    static constexpr qreal small_object_ratio_ = 2;
};

} // namespace item
