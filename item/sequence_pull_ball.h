#pragma once
#include <item/item.h>
#include <memory>

namespace item {
///顺序拉动球
class sequence_pull_ball : public item
{
public:
    static std::unique_ptr <sequence_pull_ball> make(QPointF pos, QColor color = Qt::black);

protected:
    sequence_pull_ball(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1 {0.1  * item_width, 0.2125 * item_height},
    p2 {0.7 * item_width, 0.2125 * item_height};

};
}
