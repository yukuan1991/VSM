#pragma once
#include <item/item.h>
#include <memory>

///生产工序
namespace item {

class production_sequence : public item
{
public:
    static std::unique_ptr<production_sequence> make (QPointF pos, QColor color = Qt::black);
protected:
    production_sequence(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QPointF
    p1_ {0.01 * item_width, 0.0125 * item_height},
    p2_ {0.99 * item_width, 0.0125 * item_height},
    p3_ {0.01 * item_width, 0.35 * item_height},
    p4_ {0.99 * item_width, 0.35 * item_height},
    p5_ {0.01 * item_width, 0.9875 * item_height},
    p6_ {0.99 * item_width, 0.9875 * item_height};

};
}
