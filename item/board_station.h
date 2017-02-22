#pragma once
#include "item/item.h"
#include <item/fixed_item.h>
#include <memory>

///看板站

namespace item
{

class board_station : public fixed_item
{

public:
    static std::unique_ptr <board_station> make(QPointF pos, QColor color = Qt::black);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    board_station(item* parent = nullptr);
private:


};
}

