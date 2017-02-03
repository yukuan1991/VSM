#ifndef COMMUNICATE_H
#define COMMUNICATE_H
#include <memory.h>
#include "item/item.h"

////看板以批量方式传达
namespace item {


class board_arrival : public item
{
public:
    static std::unique_ptr<board_arrival> make (QPointF pos, QColor color = Qt::black);
protected:
    board_arrival(item* parent = nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    const QVector<QPointF> polygon_shape_
    {
        {0.3 * item_width, 0.3 * item_height},
        {0.6375 * item_width, 0.3 * item_height},
        {0.7 * item_width, 0.3625 * item_height},
        {0.7 * item_width, 0.675 * item_height},
        {0.3 * item_width, 0.675 * item_height}
    };
};
}

#endif // COMMUNICATE_H
