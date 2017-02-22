#pragma once

#include "item/material_fetch_watch_board.h"
#include "item/item.h"
#include <memory>
#include "item/fixed_item.h"
///取料看板
namespace item {


class material_fetch_watch_board : public fixed_item
{
public:
    bool init ();
    static std::unique_ptr <material_fetch_watch_board> make(json data, QPointF pos, item* parent);
protected:
     explicit  material_fetch_watch_board(json data, QPointF pos, item* parent=nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
     qreal height() const override { return height() / small_object_ratio_; }
     qreal width() const override { return width() / small_object_ratio_; }
private:

  };
}

