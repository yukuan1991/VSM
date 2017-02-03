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
     p1 {0.3 * item_width, 0.125 * item_height},//p1
     p2 {0.7 * item_width, 0.125 * item_height},//p2
     p3 {0.3 * item_width, 0.375 * item_height},//
     p4 {0.7 * item_width, 0.375 * item_height},

     p5 {0.3 * item_width, 0.625 * item_height},
     p6 {0.7 * item_width, 0.625 * item_height},
     p7 {0.3 * item_width, 0.875 * item_height},
     p8 {0.7 * item_width, 0.875 * item_height};

  };
}

#endif // supermarket_rectangles_H
