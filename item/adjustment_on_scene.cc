#include "adjustment_on_scene.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {


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
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    painter->setPen(the_pen);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF (0.2 * item_width, 0.625 * item_height, 0.2 * item_width, 0.25 *item_height));///(x,y,width,heigth)
    painter->drawEllipse(QRectF (0.6 * item_width, 0.625 * item_height, 0.2 * item_width, 0.25 * item_height));
    painter->drawLine(p1_,p2);
    painter->drawLine(p3,p4);
    painter->drawLine(p5,p6);
    painter->drawLine(p3,p7);
    painter->drawLine(p5,p8);
    item::paint(painter, option, widget);

}

adjustment_on_scene::adjustment_on_scene(item* parent)
    :item(parent)
{

}
}
