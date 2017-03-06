#pragma once
#include "item/abstract_item.h"
#include "item/fixed_item.h"

namespace item {


class storage : public fixed_item
{
public:
    static std::unique_ptr<storage> make (json data, QPointF pos, abstract_item* parent);
    bool init ();
protected:
    storage(json data, QPointF pos, abstract_item* parent= nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    qreal height() const override { return fixed_item::height() / small_object_ratio_; }
    qreal width () const override { return fixed_item::width() / small_object_ratio_; }
};
}
