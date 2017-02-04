#pragma once

#include <memory>
#include <QPointF>
#include <QColor>
#include <QRectF>
#include "item/item.h"
///改善

namespace item {


class improvement : public item
{
public:
    static std::unique_ptr<improvement> make(QPointF pos, QColor color = Qt::black);

protected:
    explicit improvement(item* parent=nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1 {40,20},
    p2 {42,10},
    p3 {44,22},
    p4 {48,8},
    p5 {50,24},
    p6 {70,22},
    p7 {55,27},
    p8 {75,30},
    p9 {55,35},
    p10 {80,38},
    p11 {60,42},
    p12 {75,46},
    p13 {57,52},
    p14 {80,60},
    p15 {55,58},
    p16 {70,75},
    p17 {52,64},
    p18 {50,75},
    p19 {47,62},
    p20 {40,75},
    p21 {38,60},
    p22 {34,75},
    p23 {28,60},
    p24 {17,70},
    p25_ {8,65},
    p25 {20,57},
    p26_ {23,50},
    p26 {10,55},

    p27 {22,45},
    p28 {10,42},
    p29 {20,38},
    p30 {9,24},
    p31 {25,28},
    p32 {8,24},
    p33 {9,15},
    p34 {25,23},
    p35 {30,6},
    p36 {32,26},
    p37 {36,8};

};

}
