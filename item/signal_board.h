#pragma once

#include <memory>
#include <item/item.h>
#include <QPointF>
#include <QColor>

///信号看板
namespace item {


class signal_board : public item
{
public:
    static std::unique_ptr<signal_board> make (QPointF pos, QColor color);

protected:
    signal_board(item* parent= nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1 {0.3 * item_width, 0.3125 * item_height},
    p2 {0.7 * item_width, 0.3125 * item_height},
    p3 {0.5 * item_width, 0.6875 * item_height};
};

} /// end of item
