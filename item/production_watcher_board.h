#pragma once
#include <item/abstract_item.h>
#include <memory>
#include "item/fixed_item.h"
///生产看板
namespace item {

class production_watcher_board : public fixed_item
{
public:
    static std::unique_ptr<production_watcher_board>make(json data, QPointF pos, abstract_item* parent);
    bool init ();
protected:
    explicit production_watcher_board(json data, QPointF pos, abstract_item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    qreal width() const override { return fixed_item::width() / small_object_ratio_; }
    qreal height() const override { return fixed_item::height() / small_object_ratio_; }
private:

};
}

