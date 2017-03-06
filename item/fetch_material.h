#pragma once

#include <memory>
#include <QPointF>
#include <QColor>
#include <QRectF>
#include "item/abstract_item.h"
#include "item/fixed_item.h"
///取料

namespace item {


class fetch_material : public fixed_item
{
public:
    bool init ();

    static std::unique_ptr<fetch_material> make(json data, QPointF pos, abstract_item* parent);

protected:
    explicit fetch_material(json data, QPointF pos, abstract_item* parent=nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    qreal height() const override { return fixed_item::height() / small_object_ratio_; }
    qreal width() const override {return fixed_item::width() / small_object_ratio_; }
private:
};


}
