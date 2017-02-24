#pragma once
#include "item/fixed_item.h"
#include "item/item.h"
#include <memory>
///现场调度
namespace item {

class adjustment_on_scene : public fixed_item
{
public:
    static std::unique_ptr<adjustment_on_scene> make(json data, QPointF pos, item* parent);
    bool init();
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    adjustment_on_scene(json data, QPointF pos, item* parent = nullptr);
private:
    qreal height() const override { return fixed_item::height() / small_object_ratio_; }
    qreal width() const override { return fixed_item::width() / small_object_ratio_; }

};
}
