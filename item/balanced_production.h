﻿#pragma once
#include "item/fixed_item.h"
#include "item/abstract_item.h"
#include <QPainter>
#include <QPointF>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <memory>

///均衡生产
namespace item {

class balanced_production : public fixed_item
{

public:
    static std::unique_ptr<balanced_production> make (json data, QPointF pos, abstract_item* parent);
    bool init ();
protected:
    balanced_production(json data, QPointF pos, abstract_item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};
}

