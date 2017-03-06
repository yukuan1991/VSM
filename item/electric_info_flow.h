#pragma once

#include "item/abstract_item.h"
#include <memory>
#include "arrow_item.h"
///电子信息流
namespace item {

class electric_info_flow : public arrow_item
{
    Q_OBJECT
public:
    static unique_ptr<electric_info_flow> make (nlohmann::json data, QPointF pos, abstract_item* parent = nullptr);
    ~electric_info_flow () override;
protected:
    explicit electric_info_flow (nlohmann::json data, QPointF pos, abstract_item* parent);
    bool init ();

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
private:
    constexpr static qreal tip_width = 3;
    constexpr static qreal width = 10;

    QPointF mid_p1_;
    QPointF mid_p2_;
    QPainterPath shape_;
    QRectF bounding_rect_;
};

} // namespace item
