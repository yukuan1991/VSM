#include "production_control_department.h"
#include<memory>
#include <QPainter>
#include <QDebug>
namespace item {

std::unique_ptr<production_control_department> production_control_department::make(QPointF pos, QColor color)
{

    std::unique_ptr <production_control_department> ret(new production_control_department);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "生产控制部门";
    qDebug() << "production_control_department";
    return ret;

}

production_control_department::production_control_department(item *parent)
    :item(parent)
{

}

void production_control_department::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto x_scale = item_width_ /100;
    auto y_scale = item_height_ /80;
    QPointF p1{2 * x_scale, 2 * y_scale},
    p2{98 * x_scale, 2 * y_scale},
    p3{98 * x_scale, 78 * y_scale},
    p4{2 * x_scale, 78 * y_scale},
    p5{2 * x_scale, 35 * y_scale},
    p6{98 * x_scale,35 * y_scale},
    p7{2 *x_scale, 55 * y_scale},
    p8{50 * x_scale,55 * y_scale},
    p9{50 * x_scale, 78 * y_scale};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(std::max(0.02 * item_width_,2.0));
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1,p2,p3,p4}},Qt::WindingFill);
    painter->drawLine(p5,p6);
    painter->drawLine(p7,p8);
    painter->drawLine(p8,p9);

    item::paint(painter,option,widget);

}
}
