#include "data_box.h"
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
///数据箱
   ///修改完成
namespace item {


data_box::data_box(item* parent)
    :item (parent)
{

}

void data_box::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget);

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);
    painter->drawPolygon({{p1_, p2_, p10_, p9_}},Qt::WindingFill);
    painter->drawLine(p5_,p6_);
    painter->drawLine(p7_,p8_);
    painter->drawLine(p3_,p4_);

   item::paint(painter, option, widget);
}

std::unique_ptr<data_box> data_box::make(QPointF pos, QColor color)
{
    std::unique_ptr<data_box> ret(new data_box);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "数据箱";
    return ret;
 }
}
