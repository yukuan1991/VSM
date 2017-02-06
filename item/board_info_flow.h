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

  };
}

#endif // VS_ITEM_INFORMATION_H
