#include "information.h"
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QInputDialog>
namespace item {

std::unique_ptr<information> information::make(json data, QPointF pos, abstract_item* parent)
{
    std::unique_ptr<information>ret(new information(move(data), pos, parent));
    if(!ret->init ())
    {
        return nullptr;
    }
    else
    {
       return ret;
    }
}

bool information::init()
{
    set_item_type("信息");
    enable_attribute ("信息名称");
    set_z_value(317);

    return true;

}

void information::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    SCOPE_EXIT {fixed_item::paint(painter, option, widget);};
    const auto item_width = width ();
    const auto item_height = height ();
    const auto x_scale = item_width / 100;
    const auto y_scale = item_height / 80;

    QPointF
    p1{1 * x_scale, 1 * y_scale},
    p2{99 * x_scale, 1 * y_scale},
    p3{ 99 * x_scale, 79 * y_scale},
    p4{ 1 * x_scale, 79 * y_scale};
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1,p2,p3,p4}}, Qt::WindingFill);
    auto item_name = name();

    if(item_name.empty())
    {
        return;
    }

    QFontMetricsF metrics (painter->font());
    auto text_width = metrics.width(item_name.data());
    auto text_height = metrics.height();
    auto center = QPointF (item_width / 2, (p1.y() + p4.y()) / 2);
    painter->drawText(QRectF (center - QPointF (text_width / 2, text_height / 2), QSizeF (text_width, text_height)), item_name.data());
}

information::information(json data, QPointF pos, abstract_item *parent)
    :fixed_item(move(data), pos, parent)
 {

}

void information::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    abstract_item::mouseDoubleClickEvent (event);
    auto old_name = name ();
    bool confirmed = false;
    auto name = QInputDialog::getText(nullptr, "", "信息名称:",
                                              QLineEdit::Normal, old_name.data(), &confirmed);
    if (confirmed)
    {
        set_name (name.trimmed ().toStdString());
    }
}
}


