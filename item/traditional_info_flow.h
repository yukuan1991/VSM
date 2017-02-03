#ifndef ITEM_TRADITIONAL_INFO_FLOW_H
#define ITEM_TRADITIONAL_INFO_FLOW_H
#include "item/item.h"

namespace item {

class traditional_info_flow : public item::item
{
public:
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    static std::unique_ptr<traditional_info_flow> make (QPointF p1, QPointF p2, QColor color = Qt::black,
                                                item* parent = nullptr);
    ~traditional_info_flow () override;

protected:
    explicit traditional_info_flow (QPointF p1, QPointF p2, item* parent = nullptr, QColor color = Qt::black);
    bool init ();

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
private:
    QPointF p1_, p2_;
    QPointF body_end_, neck1_, neck2_;
    QPointF outer_p1_, outer_p2_, outer_neck1_, outer_tip_, outer_neck2_, outer_p4_, outer_p3_;
    constexpr static qreal tip_width = 3;
    constexpr static qreal tip_length = 10;
    constexpr static qreal bound_width = 5;
};

} // namespace item

#endif // ITEM_TRADITIONAL_INFO_FLOW_H
