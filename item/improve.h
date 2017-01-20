#ifndef CIRCLE_H
#define CIRCLE_H
#include <memory>
#include <QPointF>
#include <QColor>
#include <QRectF>
#include "item/item.h"
///取料

namespace item {


class improve : public item
{
public:
    static std::unique_ptr<improve> make(QPointF pos, QColor color = Qt::black);

protected:
    explicit improve(item* parent=nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1 {40,60},
    p2 {20,58},
    p3 {40,55},
    p4 {20,50},
    p5 {35,45},
    p6 {20,38},
    p7 {45,40},
    p8 {38,28},
    p9 {50,40},
    p10 {60,20},
    p11 {60,40},
    p12 {70,35},
    p13 {68,40},
    p14 {60,50},
    p15 {70,50},
    p16 {60,60},
    p17 {70,68},
    p18 {60,60},
    p19 {50,65},
    p20 {40,75};

};

}
#endif // CIRCLE_H
