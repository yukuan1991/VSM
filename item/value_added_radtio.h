#pragma once

#include "item/item.h"
#include "item/fixed_item.h"

///价值增值比
namespace item {

class value_added_radtio : public fixed_item
{
public:
    bool init ();
    static std::unique_ptr<value_added_radtio> make (json data, QPointF pos, item* parent);
protected:
    value_added_radtio(json data, QPointF pos, item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void paint_attribute (QPainter* painter) override;
    QRectF boundingRect () const override;

};
}
