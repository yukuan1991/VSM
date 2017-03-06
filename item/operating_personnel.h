#pragma once
#include <item/abstract_item.h>
#include <memory>
#include "item/fixed_item.h"
////操作员
namespace item {


class operating_personnel : public fixed_item
{
public:
    bool init ();
    static std::unique_ptr <operating_personnel> make(json data, QPointF pos, abstract_item* parent);


protected:
    operating_personnel(json data, QPointF pos, abstract_item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    qreal height() const override { return fixed_item::height() / small_object_ratio_; }
    qreal width() const override { return fixed_item::width() / small_object_ratio_; }
};
}

