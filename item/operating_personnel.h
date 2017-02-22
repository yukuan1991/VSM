#ifndef VS_ITEM_CONVEY_H
#define VS_ITEM_CONVEY_H
#include <item/item.h>
#include <memory>
#include "item/fixed_item.h"
////操作员
namespace item {


class operating_personnel : public fixed_item
{
public:
    bool init ();
    static std::unique_ptr <operating_personnel> make(json data, QPointF pos, item* parent);

protected:
    operating_personnel(json data, QPointF pos, item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
}

#endif // VS_ITEM_CONVEY_H
