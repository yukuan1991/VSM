#pragma once

#include <memory>
#include <QPointF>
#include <QColor>
#include <QRectF>
#include "item/item.h"
#include "item/fixed_item.h"
///取料

namespace item {


class fetch_material : public fixed_item
{
public:
    bool init ();

    static std::unique_ptr<fetch_material> make(json data, QPointF pos, item* parent);

protected:
    explicit fetch_material(json data, QPointF pos, item* parent=nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    int startAngle = 1 * item_width_ * 16;
    int spanAngle = 1.7 * item_width_ * 16;
    qreal x = 0.2 * item_width_;///20
    qreal y = 0.25 * item_height_; ///20
    qreal width = 0.8 * item_width_;
    qreal heigth = 0.75 * item_height_;



};


}
