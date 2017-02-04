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
    p1_{0.39 * item_width ,0.0125 * item_height},
    p2_{0.60 * item_width,0.0125 * item_height},
    p3_{0.39 * item_width,0.3375 * item_height},
    p4_{0.60 * item_width,0.3375 * item_height},
    p5_{0.39 * item_width,0.6625 * item_height},
    p6_{0.60 * item_width,0.6625 * item_height},
    p7_{0.39 * item_width,0.9875 * item_height},
    p8_{0.6 * item_width,0.9875 * item_height};
};
}

#endif // BUFFER_H
