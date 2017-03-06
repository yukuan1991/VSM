#pragma once
#include "item/arrow_item.h"

namespace item {

class product_to_customer : public arrow_item
{
public:
    Q_OBJECT
public:
    static unique_ptr<product_to_customer> make (nlohmann::json data, QPointF pos, abstract_item* parent = nullptr);
    ~product_to_customer () override;
protected:
    explicit product_to_customer (nlohmann::json data, QPointF pos, abstract_item* parent);
    bool init ();

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;

private:
    QPointF body_p1_, body_p2_, body_p3_, body_p4_, body_neck1_, body_neck2_, arrow_tip_;
    QPainterPath shape_;
    QRectF bounding_rect_;

    constexpr static qreal head_distance = 25;
    constexpr static qreal width = 5;
    constexpr static qreal fill_distance = 8;
    constexpr static qreal head_ratio = 5;
};

}
