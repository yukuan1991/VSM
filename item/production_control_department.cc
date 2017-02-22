#include "production_control_department.h"
#include<memory>
#include <QPainter>
#include <QDebug>
#include <QInputDialog>
namespace item {

std::unique_ptr<production_control_department> production_control_department::make(QPointF pos, QColor color)
{
    std::unique_ptr <production_control_department> ret(new production_control_department);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    set_item_type("生产控制部门");
    return ret;
}

production_control_department::production_control_department(item *parent)
    :item(parent)
{
    set_attribute("生产计划安排方式");
}

void production_control_department::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SCOPE_EXIT { item::paint(painter,option,widget); };

    auto const x_scale = item_width_ /100;
    auto const y_scale = item_height_ /80;
    const QPointF p1{2 * x_scale, 2 * y_scale},
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

    auto item_name = name();
    if(item_name.empty())
    {
        return;
    }

    QFontMetricsF metrics (painter->font());
    auto width = metrics.width(item_name.data());
    auto height = metrics.height();
    auto center = QRectF (p1, p6).center();
    painter->drawText(QRectF (center - QPointF (width / 2, height / 2), QSizeF (width, height)), item_name.data());

    auto plan_method = attribute ("生产计划安排方式");
    center = QRectF (p7, p9).center ();
    width = metrics.width(plan_method.data ());

    painter->drawText(QRectF (center - QPointF (width / 2, height / 2), QSizeF (width, height)), plan_method.data ());
}

void production_control_department::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED (event);
    auto old_name = name ();
    bool confirmed = false;
    auto company_name = QInputDialog::getText(nullptr, "", "名称:",
                                              QLineEdit::Normal, old_name.data(), &confirmed);
    if (confirmed)
    {
        set_name (company_name.trimmed ().toStdString());
    }
}

void production_control_department::paint_attribute(QPainter *painter)
{
    Q_UNUSED (painter);
}

}
