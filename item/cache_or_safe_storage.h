#ifndef BUFFER_H
#define BUFFER_H
#include "item/item.h"
#include <memory.h>
///缓冲或者安全库存
namespace item {


class cache_or_safe_storage : public item
{

public:
   static std::unique_ptr <cache_or_safe_storage> make(QPointF pos, QColor color = Qt::black);
protected:
    cache_or_safe_storage(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1{0.35 * item_width ,0.125 * item_height},
    p2{0.65 * item_width,0.125 * item_height},
    p3{0.35 * item_width,0.875 * item_height},
    p4{0.65 * item_width,0.875 * item_height},
    p5{0.35 * item_width,0.375 * item_height},
    p6{0.65 * item_width,0.375 * item_height},
    p7{0.35 * item_width,0.625 * item_height},
    p8{0.65 * item_width,0.625 * item_height};
};
}

#endif // BUFFER_H
