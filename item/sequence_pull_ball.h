#pragma once
#include <item/abstract_item.h>
#include <memory>
#include "item/fixed_item.h"

namespace item {
///顺序拉动球
class sequence_pull_ball : public fixed_item
{
public:
    static std::unique_ptr <sequence_pull_ball> make(json data, QPointF pos, abstract_item* parent);
    bool init ();
protected:
    sequence_pull_ball(json data, QPointF pos, abstract_item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
};
}
