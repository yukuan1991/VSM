#ifndef STORAGE_H
#define STORAGE_H
#include "item/item.h"
#include "item/fixed_item.h"

namespace item {


class storage : public fixed_item
{
public:
    static std::unique_ptr<storage> make (QPointF pos, QColor color);

protected:
    storage(item* parent= nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
}
#endif // STORAGE_H
