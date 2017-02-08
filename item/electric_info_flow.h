#pragma once

#include "item/item.h"
#include <memory>
///电子信息流
namespace item {

class electric_info_flow : public item::item
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    static std::unique_ptr<electric_info_flow> make (QPointF p1, QPointF p2, QColor color = Qt::black,
                                                item* parent = nullptr);
    ~electric_info_flow () override;

protected:
    explicit electric_info_flow (QPointF p1, QPointF p2, item* parent = nullptr, QColor color = Qt::black);
    bool init ();

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
private:
    QPointF start_, end_;
    QPointF mid_p1_, mid_p2_, body_end_, neck1_, neck2_;

    constexpr static qreal width = 10;
    constexpr static qreal tip_width = 3;
    constexpr static qreal tip_length = 10;
};

} // namespace item
