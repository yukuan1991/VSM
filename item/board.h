#ifndef VS_ITEM_BOARD_H
//#define
#include <item/item.h>
#include <memory>

///看板站

namespace item
{

class board : public item
{
public:
   static std::unique_ptr <board> make(QPointF pos, QColor color = Qt::black);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    board(item* parent = nullptr);
private:
    QPointF
    p1 {0.2 * item_width, 0.125 * item_height},
    p2 {0.8 * item_width, 0.125 * item_height},
    p3 {0.25 * item_width, 0.5 * item_height},
    p4 {0.5 * item_width, 0.5 * item_height},

    p5 {0.75 * item_width, 0.5 * item_height},
    p6 {0.25 * item_width, 0.875 * item_height},
    p7 {0.5 * item_width, 0.875 * item_height},
    p8 {0.75 * item_width, 0.875 * item_height};

  };
}

#endif // VS_ITEM_BOARD_H
