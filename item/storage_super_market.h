#ifndef supermarket_rectangles_H
#define supermarket_rectangles_H
#include <item/item.h>
#include <memory>

///库存超市
namespace item {


class storage_super_market : public item
{
public:
   static std::unique_ptr<storage_super_market> make(QPointF pos,QColor color);

protected:
    storage_super_market(item* parent = nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
     QPointF
     p1_ {0.29 * item_width, 0.0125 * item_height},//p1
     p2_ {0.71 * item_width, 0.0125 * item_height},//p2
     p3_ {0.29 * item_width, 0.3375 * item_height},//
     p4_ {0.71 * item_width, 0.3375 * item_height},

     p5_ {0.29 * item_width, 0.6625 * item_height},
     p6_ {0.71 * item_width, 0.6625 * item_height},
     p7_ {0.29 * item_width, 0.9875 * item_height},
     p8_ {0.71 * item_width, 0.9875 * item_height};

  };
}

#endif // supermarket_rectangles_H
