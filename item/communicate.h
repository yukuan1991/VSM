#ifndef COMMUNICATE_H
#define COMMUNICATE_H
#include <memory.h>
#include "item/item.h"

////看板以批量方式传达
namespace item {


class communicate : public item
{
public:
    static std::unique_ptr<communicate> make (QPointF pos, QColor color = Qt::black);
protected:
    communicate(item* parent = nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
     QPointF
     p1_botton {0.1 * item_width,0.5 * item_height },
     p2_botton {0.4 * item_width, 0.5 * item_height},
     p3_botton{0.5* item_width, 0.5625 * item_height},
     p4_botton {0.1 * item_width, 0.875 * item_height},
     p5_botton {0.5 * item_width, 0.875 * item_height},
     p1_middle {0.2 * item_width, 0.5 * item_height},
     p2_middle {0.2 * item_width, 0.3125 * item_height},
     p3_middle{0.6 * item_width, 0.3125 * item_height},
     p4_middle {0.7 * item_width, 0.4375 * item_height},
     p5_middle {0.7 * item_width, 0.75 * item_height},
     p6_middle{0.5 * item_width,0.75 * item_height },
     p1_top {0.3 * item_width,0.3125 * item_height},
     p2_top {0.3 * item_width, 0.125 * item_height},
     p3_top{0.7 * item_width , 0.125 * item_height},
     p4_top {0.8 * item_width, 0.25 * item_height} ,
     p5_top {0.8 * item_width , 0.625 * item_height},
     p6_top{0.7 * item_width,0.625 * item_height};




};
}

#endif // COMMUNICATE_H
