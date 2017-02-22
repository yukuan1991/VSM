#pragma once
#include "item/item.h"


namespace item {

class fixed_item : public item::item
{
public:
    virtual qreal width () { return item_width_; }
    virtual qreal height () { return item_height_; }
    virtual void paint_attribute (QPainter* painter);
protected:
    explicit fixed_item (QGraphicsItem *parent = 0);
};

} // namespace item
