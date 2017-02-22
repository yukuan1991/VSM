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
    bool init ();
    static std::unique_ptr<board_arrival> make (json data, QPointF pos, item* parent);
protected:
    board_arrival(json data, QPointF pos, item* parent = nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
     qreal width () const override  {  return fixed_item::width() / small_object_ratio_; }
     qreal height () const override  {  return fixed_item::height() / small_object_ratio_; }


};
}

#endif // COMMUNICATE_H
