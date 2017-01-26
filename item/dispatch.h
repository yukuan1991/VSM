#ifndef DISPATCH_H
#define DISPATCH_H
#include "item/item.h"
#include <memory>
///现场调度
namespace item {


class dispatch : public item
{
public:
    static std::unique_ptr<dispatch> make(QPointF pos,QColor = Qt::black);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    dispatch(item* parent = nullptr);
private:
    QPointF
       p1 {0.4 * item_width,0.75 * item_height},
       p2 {0.6 * item_width,0.75 * item_height},
       p3 {0.8 * item_width,0.300 * item_height},
       p4 {0.75 * item_width,0.625 * item_height},
       p5 {0.3 * item_width,0.3 * item_height},
       p6 {0.23 * item_width,0.65 * item_height},
       p7 {0.83 * item_width,0.38 * item_height},
       p8 {0.33 * item_width,0.38 * item_height};

  };
}

#endif // DISPATCH_H
