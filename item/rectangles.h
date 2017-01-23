#ifndef VS_ITEM_ONE_RECTANGLES_H
#define VS_ITEM_ONE_RECTANGLES_H
#include <item/item.h>
#include <memory>

///生产工序
namespace item {


class rectangles : public item
{
public:
     static std::unique_ptr<rectangles> make (QPointF pos, QColor color = Qt::black);

protected:
    rectangles(item* parent=nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
     QPointF
     p1 {0.25 * item_width, 0.125 * item_height},
     p2 {0.75 * item_width, 0.125 * item_height},
     p3 {0.25 * item_width, 0.875 * item_height},
     p4 {0.75 * item_width, 0.875 * item_height},

     p5 {0.25 * item_width, 0.3125 * item_height},
     p6 {0.75 * item_width, 0.3125 * item_height};

  };
}

#endif // VS_ITEM_ONE_RECTANGLES_H
