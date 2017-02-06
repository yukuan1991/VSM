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
    QPointF
    p1 {42 , 60},
    p2 {60, 60},
    p3 {22, 54},
    p4 {30, 20},
    p5 {33, 28},
    p6 {78, 53},
    p7 {82, 20},
    p8 {85, 28};
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    painter->setPen(the_pen);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF (20, 50, 22, 22));///(x,y,width,heigth),不知道x,y到底是哪点的坐标
    painter->drawEllipse(QRectF (60,50, 22, 22));
    painter->drawLine(p1,p2);
    painter->drawLine(p3,p4);
    painter->drawLine(p4,p5);
    painter->drawLine(p6,p7);
    painter->drawLine(p7,p8);
    item::paint(painter, option, widget);

}

adjustment_on_scene::adjustment_on_scene(item* parent)
    :item(parent)
{

}
}
