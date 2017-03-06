#pragma once
#include "item/arrow_item.h"

namespace item {

class traditional_info_flow : public arrow_item
{
    Q_OBJECT
public:
    static unique_ptr<traditional_info_flow> make (nlohmann::json data, QPointF pos, abstract_item* parent = nullptr);
    ~traditional_info_flow () override;
protected:
    explicit traditional_info_flow (nlohmann::json data, QPointF pos, abstract_item* parent);
    bool init ();

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
private:
    constexpr static qreal tip_width = 3;
    constexpr static qreal tip_length = 10;
    QPainterPath shape_;
    QRectF bounding_rect_;
};

} // namespace item


