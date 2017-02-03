#pragma once

#include "item/material_fetch_watch_board.h"
#include "item/item.h"
#include <memory>
///取料看板
namespace item {


class material_fetch_watch_board : public item
{
public:
    static std::unique_ptr <material_fetch_watch_board> make(QPointF pos, QColor = Qt::black);
protected:
     explicit  material_fetch_watch_board(item* parent=nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
     QPointF //shape1_, shape2_, shape3_, shape4_, shape5_;
     p1{0.05 * item_width,0.125 * item_height},
     p2{0.25 * item_width,0.125 * item_height},
     p3{0.45 * item_width,0.125 * item_height},
     p4{0.72 * item_width,0.125 * item_height},
     p5{0.75 * item_width,0.125 * item_height},
     p6{0.85 * item_width, 0.25 * item_height},
     p7{0.95 * item_width,0.375 * item_height},
     p8{0.05 * item_width,0.375 * item_height},
     p9{0.05 * item_width,0.625 * item_height},
     p10{0.05 * item_width,0.75 * item_height},
     p11{0.25 * item_width,0.75 * item_height},
     p12{0.45 * item_width,0.75 * item_height},
     p13{0.65 * item_width,0.75 * item_height},
     p14{0.95 * item_width, 0.75 * item_height};
  };
}

