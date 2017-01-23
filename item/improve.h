#pragma once

#include <memory>
#include <QPointF>
#include <QColor>
#include <QRectF>
#include "item/item.h"
///改善

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
    p1 {0.4 * item_width,0.75 * item_height},
    p2 {0.2 * item_width,0.725 * item_height},
    p3 {0.4 * item_width,0.6875 * item_height},
    p4 {0.2 * item_width,0.625 * item_height},
    p5 {0.35 * item_width,0.5625 * item_height},
    p6 {0.2 * item_width,0.475 * item_height},
    p7 {0.45 * item_width,0.5 * item_height},
    p8 {0.38 * item_height,0.35 * item_height},
    p9 {0.5 * item_width,0.5 * item_height},
    p10 {0.6 * item_width,0.25 * item_height},
    p11 {0.6 * item_width,0.5 * item_height},
    p12 {0.7 * item_width,0.4375 * item_height},
    p13 {0.68 * item_width,0.5 * item_height},
    p14 {0.6 * item_width,0.625 * item_height},
    p15 {0.7 * item_width,0.625 * item_height},
    p16 {0.6 * item_width,0.75 * item_height},
    p17 {0.7 * item_width,0.85 * item_height},
    p18 {0.6 * item_width,0.75 * item_height},
    p19 {0.5* item_width,0.8125 * item_height},
    p20 {0.4 * item_width,0.9375 * item_height};

};

}
