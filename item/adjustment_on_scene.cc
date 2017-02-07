#include "adjustment_on_scene.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {

adjustment_on_scene::adjustment_on_scene(item* parent)
    :item(parent)
{

}

std::unique_ptr<adjustment_on_scene> adjustment_on_scene::make(QPointF pos, QColor color)
{
    std::unique_ptr <adjustment_on_scene> ret (new adjustment_on_scene);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "现场调度";
    return ret;

}

void adjustment_on_scene::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF
    p1 {0.42 * item_width , 0.75 * item_height},
    p2 {0.6 * item_width, 0.75 * item_height},
    p3 {0.22 * item_width, 0.675 * item_height},
    p4 {0.3 * item_width, 0.25 * item_height},
    p5 {0.33 * item_width, 0.35 * item_height},
    p6 {0.78 * item_width, 0.6625 * item_height},
    p7 {0.82 * item_width, 0.25 * item_height},
    p8 {0.85 * item_width, 0.35 * item_height};
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF (0.2 * item_width, 0.625 * item_height, 0.22 * item_width, 0.275 * item_height));
    painter->drawEllipse(QRectF (0.6 * item_width,0.625 * item_height, 0.22 * item_width, 0.275 * item_height));
    painter->drawLine(p1,p2);
    painter->drawLine(p3,p4);
    painter->drawLine(p4,p5);
    painter->drawLine(p6,p7);
    painter->drawLine(p7,p8);
    item::paint(painter, option, widget);

}

}
