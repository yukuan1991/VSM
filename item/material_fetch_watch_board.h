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

  };
}

