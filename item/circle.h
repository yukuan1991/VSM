#pragma once

#include <memory>
#include <QPointF>
#include <QColor>
#include <QRectF>
#include "item/item.h"
///取料

namespace item {


class circle : public item
{
public:
    static std::unique_ptr<circle> make(QPointF pos, QColor color = Qt::black);

protected:
    explicit circle(item* parent=nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    int startAngle = 1 * item_width * 16;
    int spanAngle = 1.7 * item_width * 16;
    constexpr static qreal x = 0.2 * item_width;///20
    constexpr static qreal y = 0.25 * item_height; ///20
    constexpr static qreal width = 0.8 * item_width;
    constexpr static qreal heigth = 0.75 * item_height;

    QPointF
    p1 {0.75 * item_width, 0.8125 * item_height},
    p2 {0.82 * item_width, 0.9 * item_height},
    p3 {0.87 * item_width,0.75 * item_height};

};


}
