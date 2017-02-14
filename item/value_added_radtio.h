#ifndef VALUE_ADDED_RADTIO_H
#define VALUE_ADDED_RADTIO_H
#include "item/item.h"
#include <memory>

///价值增值比
namespace item {

class value_added_radtio : public item
{
public:
    std::unique_ptr<value_added_radtio> make (QPointF pos, QColor color = Qt::black);
protected:
    value_added_radtio(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
}
#endif // VALUE_ADDED_RADTIO_H
