#include "communicate.h"
#include <memory.h>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<communicate> communicate::make(QPointF pos, QColor color)
{
    std::unique_ptr <communicate> ret(new communicate);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;


}

communicate::communicate(item* parent)
    :item(parent)
{

}

void communicate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(1.0);
    painter->setPen(the_pen);
    painter->drawPolygon({{p1_botton, p2_botton, p3_botton,p5_botton,p4_botton}}, Qt::WindingFill);
    painter->drawLine(p1_middle,p2_middle);
    painter->drawLine(p2_middle,p3_middle);
    painter->drawLine(p3_middle,p4_middle);
    painter->drawLine(p4_middle,p5_middle);
    painter->drawLine(p5_middle,p6_middle);
    painter->drawLine(p1_top,p2_top);
    painter->drawLine(p2_top,p3_top);
    painter->drawLine(p3_top,p4_top);
    painter->drawLine(p4_top,p5_top);
    painter->drawLine(p5_top,p6_top);
    item::paint(painter, option, widget);




 }
}
