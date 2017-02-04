#include "improvement.h"
#include <QPointF>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QRectF>
///改善

namespace item {


std::unique_ptr<improvement> improvement::make(QPointF pos, QColor color)
{
    std::unique_ptr<improvement>ret(new improvement);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "改善";
    return ret;
}

improvement::improvement(item *parent)
    :item(parent)
{


}

void improvement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(1.0);
    painter->setPen(the_pen);
    painter->setPen(Qt::red);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawLine(p1,p2);
    painter->drawLine(p2,p3);
    painter->drawLine(p3,p4);
    painter->drawLine(p4,p5);
    painter->drawLine(p5,p6);
    painter->drawLine(p6,p7);
    painter->drawLine(p7,p8);
    painter->drawLine(p8,p9);
    painter->drawLine(p9,p10);
    painter->drawLine(p10,p11);
    painter->drawLine(p11,p12);
    painter->drawLine(p12,p13);
    painter->drawLine(p13,p14);
    painter->drawLine(p14,p15);
    painter->drawLine(p15,p16);
    painter->drawLine(p16,p17);
    painter->drawLine(p17,p18);
    painter->drawLine(p18,p19);
    painter->drawLine(p19,p20);
    painter->drawLine(p20,p21);
    painter->drawLine(p21,p22);
    painter->drawLine(p22,p23);
    painter->drawLine(p23,p24);
    painter->drawLine(p24,p25);
    painter->drawLine(p25,p25_);
    painter->drawLine(p25_,p26_);
    painter->drawLine(p26_,p26);
    painter->drawLine(p26,p27);
    painter->drawLine(p27,p28);
    painter->drawLine(p28,p29);
    painter->drawLine(p29,p30);
    painter->drawLine(p30,p31);
    painter->drawLine(p31,p32);
    painter->drawLine(p31,p33);
    painter->drawLine(p33,p34);
    painter->drawLine(p34,p35);
    painter->drawLine(p35,p36);
    painter->drawLine(p36,p37);
    painter->drawLine(p37,p1);

    item::paint(painter, option, widget);
}

}
