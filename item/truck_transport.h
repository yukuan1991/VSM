#ifndef TRUCK_TRANSPORT_H
#define TRUCK_TRANSPORT_H
#include "item/item.h"
#include "item/fixed_item.h"
namespace  item {

class truck_transport : public fixed_item
{
public:
    static std::unique_ptr<truck_transport> make (json data,QPointF pos, item* parent);
    bool init ();
protected:
    truck_transport(json data, QPointF pos, item* parent= nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};
}
#endif // TRUCK_TRANSPORT_H
