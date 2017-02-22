#pragma once
#include <item/item.h>
#include <memory>
#include "item/fixed_item.h"

///生产工序
namespace item {

class production_sequence : public fixed_item
{
public:
    bool init ();
    static std::unique_ptr<production_sequence> make (json data, QPointF pos, item* parent);
protected:
    production_sequence(json data, QPointF pos, item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


};
}
