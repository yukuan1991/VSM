#include "adjustment_on_scene.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {
///修改成item_width * 1/4
adjustment_on_scene::adjustment_on_scene(json data, QPointF pos, item* parent = nullptr)
    :fixed_item(::move (data), pos, parent)
{

//      item_width_ = item_width_ * ( 1 / small_object_ratio);
//      item_height_ = item_height_ * ( 1 / small_object_ratio);



}

std::unique_ptr<adjustment_on_scene> adjustment_on_scene::make(json data, QPointF pos, item* parent)
{
    std::unique_ptr<adjustment_on_scene>ret(new adjustment_on_scene (::move (data), pos, parent));
    if (!ret->init ())
    {
        return nullptr;
    }
    else
    {
        return ret;
    }

}

bool adjustment_on_scene::init()
{
    set_item_type("现场调度");
    set_attribute ("库存量");
    set_attribute ("原生产计划");
    set_attribute ("更改后生产计划");
    set_z_value(307);

    return true;

}

void adjustment_on_scene::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF
    p1 {0.42 * item_width_ , 0.75 * item_height_},
    p2 {0.6 * item_width_, 0.75 * item_height_},
    p3 {0.22 * item_width_, 0.675 * item_height_},
    p4 {0.3 * item_width_, 0.25 * item_height_},
    p5 {0.33 * item_width_, 0.35 * item_height_},
    p6 {0.78 * item_width_, 0.6625 * item_height_},
    p7 {0.82 * item_width_, 0.25 * item_height_},
    p8 {0.85 * item_width_, 0.35 * item_height_};
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(std::max(item_width_ * 0.02,2.0));
    painter->setPen(the_pen);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF (0.2 * item_width_, 0.625 * item_height_, 0.22 * item_width_, 0.275 * item_height_));
    painter->drawEllipse(QRectF (0.6 * item_width_,0.625 * item_height_, 0.22 * item_width_, 0.275 * item_height_));
    painter->drawLine(p1,p2);
    painter->drawLine(p3,p4);
    painter->drawLine(p4,p5);
    painter->drawLine(p6,p7);
    painter->drawLine(p7,p8);
    item::paint(painter, option, widget);

}

}
