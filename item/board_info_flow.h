#pragma once
#include <item/abstract_item.h>
#include "utility/memory.hpp"
#include "utility/containers.hpp"
/////看板用流信息
namespace item {


class board_info_flow : public abstract_item
{
public:
    static unique_ptr <board_info_flow> make (json data, QPointF pos, abstract_item* parent = nullptr);

protected:
    board_info_flow(json data, QPointF pos, abstract_item * parent);
    bool init ();
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
private:
    vector<QLineF> lines_;
    QPainterPath shape_;
    QRectF bounding_rect_;
    static constexpr qreal tip_length = 10;
    static constexpr qreal tip_width = 4;
};
}

