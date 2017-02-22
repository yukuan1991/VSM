#ifndef BUFFER_H
#define BUFFER_H
#include "item/fixed_item.h"
#include "item/item.h"
#include <memory.h>
///缓冲或者安全库存
namespace item {


class cache_or_safe_storage : public fixed_item
{

public:
   static std::unique_ptr <cache_or_safe_storage> make(QPointF pos, QColor color = Qt::black);
protected:
    cache_or_safe_storage(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:

};
}

#endif // BUFFER_H
