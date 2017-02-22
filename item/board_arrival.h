#ifndef COMMUNICATE_H
#define COMMUNICATE_H
#include <memory.h>
#include "item/fixed_item.h"
#include "item/item.h"

////看板以批量方式传达
namespace item {


class board_arrival : public fixed_item
{
public:
    static std::unique_ptr<board_arrival> make (QPointF pos, QColor color = Qt::black);
protected:
    board_arrival(item* parent = nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};
}

#endif // COMMUNICATE_H
