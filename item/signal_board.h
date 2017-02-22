#pragma once

#include <memory>
#include <item/item.h>
#include <QPointF>
#include <QColor>
#include "item/fixed_item.h"


///信号看板
namespace item {


class signal_board : public fixed_item
{
public:
    static std::unique_ptr<signal_board> make (QPointF pos, QColor color);

protected:
    signal_board(item* parent= nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:

};

} /// end of item
