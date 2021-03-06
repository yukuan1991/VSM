﻿#pragma once
#include "item/abstract_item.h"
#include <item/fixed_item.h>
#include <memory>

///看板站

namespace item
{

class board_station : public fixed_item
{

public:
    bool init ();
    static std::unique_ptr <board_station> make(json data, QPointF pos, abstract_item* parent);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    board_station(json data, QPointF pos, abstract_item* parent = nullptr);
private:


};
}

