#include "other_company.h"
#include "QStyleOptionGraphicsItem"
#include "QPainter"
namespace item {


std::unique_ptr<other_company> other_company::make(QPointF pos, QColor color)
{
    std::unique_ptr <other_company> ret(new other_company);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "其他公司";
    return ret;

}

other_company::other_company(item * parent)
    :item(parent)
{
    set_attribute("需求量");
    set_attribute("包装方式");
    set_attribute("工作班数");
}

void other_company::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);

    auto x_scale = item_width / 100;
    auto y_scale =item_height / 80;
    const QPointF
    p1 {1 * x_scale, 30 * y_scale},
    p2 {33 * x_scale,1 * y_scale},
    p3 {33 * x_scale,26 * y_scale},
    p4 {66 * x_scale,1 * y_scale},
    p5 {66 * x_scale,26 * y_scale},
    p6 {99 * x_scale,4 * y_scale},
    p7 {99 * x_scale,79 * y_scale},
    p8 {1 * x_scale,79 * y_scale};
    painter->drawPolygon({{p1,p2,p3,p4,p5,p6,p7,p8}},Qt::WindingFill);

    item::paint(painter, option, widget);
}

}
