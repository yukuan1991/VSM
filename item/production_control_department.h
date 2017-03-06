#pragma once
#include "item/abstract_item.h"
#include "item/fixed_item.h"

///生产控制部门
namespace item {


class production_control_department : public fixed_item
{
public :
    bool init ();
    static std::unique_ptr<production_control_department> make(json data, QPointF pos, abstract_item* parent);
protected:
    production_control_department(json data, QPointF pos, abstract_item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void paint_attribute (QPainter* painter) override;
};
}
