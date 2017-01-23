#ifndef round_H
#define round_H
#include <item/item.h>
#include <memory>
///顺序拉动球
namespace item {


class round : public item
{
public:
    static std::unique_ptr <round> make(QPointF pos, QColor color = Qt::black);

protected:
    round(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1 {0.1  * item_width, 0.2125 * item_height},
    p2 {0.7 * item_width, 0.2125 * item_height};

 };
}
#endif // round_H
