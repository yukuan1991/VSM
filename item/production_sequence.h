#pragma once
#include <item/item.h>
#include <memory>
#include "item/fixed_item.h"

///生产工序
namespace item {

class production_sequence : public fixed_item
{
public:
    static std::unique_ptr<production_sequence> make (QPointF pos, QColor color = Qt::black);
protected:
    production_sequence(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


};
}
