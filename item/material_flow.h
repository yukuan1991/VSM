#ifndef ITEM_MATERIAL_FLOW_H
#define ITEM_MATERIAL_FLOW_H

#include "item/item.h"

namespace item {

class material_flow : public item::item
{
public:
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    static std::unique_ptr<material_flow> make (QPointF p1, QPointF p2, QColor color = Qt::black,
                                                item* parent = nullptr);
protected:
    explicit material_flow (QPointF p1, QPointF p2, item* parent = nullptr);

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;

private:
    QPointF p1_, p2_;

    QPointF body_p1_, body_p2_, body_p3_, body_p4_, neck1_, neck2_, arrow_tip_;
    QPointF outer_p1_, outer_p2_, outer_neck1_, outer_tip_, outer_neck2_, outer_p4_, outer_p3_;

    constexpr static qreal width = 5;
    constexpr static qreal fill_distance = 8;
    constexpr static qreal head_ratio = 5;
    constexpr static qreal outer_gap = 2;
};

} // namespace item

#endif // ITEM_MATERIAL_FLOW_H
