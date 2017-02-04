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
     p1_{0.01 * item_width,0.0125 * item_height},
     p2_{0.25 * item_width,0.0125 * item_height},
     p3_{0.5 * item_width,0.0125 * item_height},
     p4_{0.74 * item_width,0.0125 * item_height},
     p5_{0.85 * item_width,0.0125 * item_height},
     p6_{0.95 * item_width, 0.125 * item_height},
     p7_{0.99 * item_width,0.2 * item_height},
     p8_{0.99 * item_width,0.4875 * item_height},
     p9_{0.99 * item_width,0.9875 * item_height},
     p10_{0.74* item_width,0.9875 * item_height},
     p11_{0.50 * item_width,0.9875 * item_height},
     p12_{0.25 * item_width,0.9875 * item_height},
     p13_{0.01 * item_width,0.9875 * item_height},
     p14_{0.01 * item_width, 0.4875 * item_height};
  };
}

