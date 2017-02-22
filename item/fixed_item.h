#pragma once
#include "item/item.h"


namespace item {

class fixed_item : public item
{
public:
    virtual qreal width () = 0;
    virtual qreal height () = 0;
    virtual void paint_attribute (QPainter* painter);
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
protected:
    explicit fixed_item (QGraphicsItem *parent = 0);
    void set_dash(QPainter *painter);
    constexpr static qreal standard_width () { return standard_width_; }
    constexpr static qreal standard_height () { return standard_height_; }
protected:
    static constexpr qreal standard_width_ = 100;
    static constexpr qreal standard_height_ = 80;
};

} // namespace item
