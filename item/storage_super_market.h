#pragma once
#include <item/item.h>
#include <memory>
#include "item/fixed_item.h"

///库存超市
namespace item {


class storage_super_market : public fixed_item
{
public:
   static std::unique_ptr<storage_super_market> make(json data, QPointF pos,item* parent);
   bool init ();
protected:
    storage_super_market(json data, QPointF pos, item* parent = nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:


  };
}

