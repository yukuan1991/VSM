#ifndef data_box_H
#define data_box_H
#include <item/item.h>
#include <memory>

///数据箱
namespace item {


class data_box : public item
{
public:
    static std::unique_ptr<data_box> make(QPointF pos,QColor color);
protected:
    data_box(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1_ {0.01* item_width, 0.0125 * item_height},
    p2_ {0.99 * item_width, 0.0125 * item_height},
    p3_ {0.01 * item_width, 0.25 * item_height},
    p4_ {0.99 * item_width, 0.25 * item_height},

    p5_ {0.01 * item_width, 0.5 * item_height},
    p6_ {0.99 * item_width, 0.5 * item_height},
    p7_ {0.01 * item_width, 0.7375 * item_height},
    p8_ {0.99 * item_width, 0.7375 * item_height},

    p9_ {0.01 * item_width, 0.9875 * item_height},
    p10_ {0.99 * item_width, 0.9875 * item_height};

  };
}
#endif // data_box_H
