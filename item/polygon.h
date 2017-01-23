#ifndef polygon_H
#define polygon_H
#include <item/item.h>
#include <memory>//智能指针
///生产看板
namespace item {


class polygon : public item
{
public:
    static std::unique_ptr<polygon>make(QPointF pos, QColor color = Qt::black);

protected:
    explicit polygon(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1 {0.1 * item_width, 0.2125 * item_height},
    p2 {0.7 * item_width, 0.2125 * item_height},
    p3 {0.9 * item_width, 0.4625 * item_height},
    p4 {0.9 * item_width, 0.7125 * item_height},
    p5 {0.1 * item_width, 0.7125 * item_height};

};
}

#endif // polygon_H
