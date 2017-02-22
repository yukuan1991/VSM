#ifndef STORAGE_H
#define STORAGE_H
#include "item/item.h"
#include "item/fixed_item.h"

namespace item {


class storage : public fixed_item
{
public:
    static std::unique_ptr<storage> make (json data, QPointF pos, item* parent);
    bool init ();
protected:
    storage(json data, QPointF pos, item* parent= nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    qreal height() const override { return height() / small_object_ratio_; }
    qreal width () const override { return width() / small_object_ratio_; }
};
}
#endif // STORAGE_H
