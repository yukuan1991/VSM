#pragma once

#include <item/item.h>
#include <memory>

///看板站

namespace item
{

class board_station : public item
{
public:
public:
    static std::unique_ptr <board_station> make(QPointF pos, QColor color = Qt::black);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    board_station(item* parent = nullptr);
private:
    const QPointF p1_ {0.2 * item_width, 0.125 * item_height};
    const QPointF p2_ {0.8 * item_width, 0.125 * item_height};
    const QPointF p3_ {0.25 * item_width, 0.5 * item_height};
    const QPointF p4_ {0.5 * item_width, 0.5 * item_height};
    const QPointF p5_ {0.75 * item_width, 0.5 * item_height};
    const QPointF p6_ {0.25 * item_width, 0.875 * item_height};
    const QPointF p7_ {0.5 * item_width, 0.875 * item_height};
    const QPointF p8_ {0.75 * item_width, 0.875 * item_height};

};
}

