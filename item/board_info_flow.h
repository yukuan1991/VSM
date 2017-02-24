#pragma once
#include <item/item.h>
#include "utility/memory.hpp"
#include "utility/containers.hpp"
///看板用流信息
namespace item {


class board_info_flow : public item
{
public:
    static unique_ptr <board_info_flow> make (vector<unique_ptr<QGraphicsLineItem>> tmp_lines, QColor color,
                                              item* parent = nullptr);

protected:
    board_info_flow(item* parent = nullptr);
    bool init (vector<unique_ptr<QGraphicsLineItem>> tmp_lines);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect () const override;
private:
    vector<QLineF> lines_;
    static constexpr qreal tip_length = 10;
    static constexpr qreal tip_width = 4;
};
}

