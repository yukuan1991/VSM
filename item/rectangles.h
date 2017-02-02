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
    p1 {0.25 * item_width, 0.125 * item_height},
    p2 {0.75 * item_width, 0.125 * item_height},
    p3 {0.25 * item_width, 0.875 * item_height},
    p4 {0.75 * item_width, 0.875 * item_height},

    p5 {0.25 * item_width, 0.3125 * item_height},
    p6 {0.75 * item_width, 0.3125 * item_height};

};
}
