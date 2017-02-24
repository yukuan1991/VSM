#pragma once
#include "item/fixed_item.h"
#include "item/item.h"
#include <memory.h>
///缓冲或者安全库存
namespace item {


class cache_or_safe_storage : public fixed_item
{

public:
    bool init ();
   static std::unique_ptr <cache_or_safe_storage> make(json data, QPointF pos, item* parent);
protected:
    cache_or_safe_storage(json data, QPointF pos, item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:

};
}

