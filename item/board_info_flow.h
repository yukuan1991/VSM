#ifndef VS_ITEM_INFORMATION_H
#define VS_ITEM_INFORMATION_H
#include <item/item.h>
#include <memory>
///看板用流信息
namespace item {


class board_info_flow : public item
{
public:
    static std::unique_ptr <board_info_flow> make (QPointF pos, QColor color = Qt::black);

protected:
    board_info_flow(item* parent = nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
     QPointF
     p1 {0.3 * item_width, 0.25 * item_height},
     p2 {0.7 * item_width, 0.25 * item_height},
     p3 {0.3 * item_width, 0.625 * item_height},
     p4 {0.25 * item_width, 0.625 * item_height},
     p5 {0.35 * item_width, 0.625 * item_height},
     p6 {0.3 * item_width, 0.6875 * item_height};
  };
}

#endif // VS_ITEM_INFORMATION_H
