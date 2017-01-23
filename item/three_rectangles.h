#ifndef three_rectangles_H
#define three_rectangles_H
#include <item/item.h>
#include <memory>

///数据箱
namespace item {


class three_rectangles : public item
{
public:
    static std::unique_ptr<three_rectangles> make(QPointF pos,QColor color);
protected:
    three_rectangles(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1 {0.25 * item_width, 0.125 * item_height},
    p2 {0.75 * item_width, 0.125 * item_height},
    p3 {0.25 * item_width, 0.875 * item_height},
    p4 {0.75 * item_width, 0.875 * item_height},

    p5 {0.25 * item_width, 0.3125 * item_height},
    p6 {0.75 * item_width, 0.3125 * item_height},
    p7 {0.25 * item_width, 0.5 * item_height},
    p8 {0.75 * item_width, 0.5 * item_height},
    p9 {0.25 * item_width, 0.6875 * item_height},
    p10 {0.75 * item_width, 0.6875 * item_height};

  };
}
#endif // three_rectangles_H
