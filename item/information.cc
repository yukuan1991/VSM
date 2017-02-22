#include "information.h"
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QInputDialog>
///长方形
/// 修改完成
/// 高度修改成20
namespace item {

std::unique_ptr<information> information::make(QPointF pos, QColor color)
{
    std::unique_ptr<information>ret(new information);
    ret->setPos(pos);
    ret->set_color( std::move (color));
    set_item_type("信息");
    return ret;
}

void information::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    SCOPE_EXIT {item::paint(painter, option, widget);};
    auto x_scale = (item_width_ / 100);
    auto y_scale = (item_height_ / 80 );

    QPointF
    p1{1 * x_scale, 1 * y_scale},
    p2{99 * x_scale, 1 * y_scale},
    p3{ 99 * x_scale, 79 * y_scale},
    p4{ 1 * x_scale, 79 * y_scale};
    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidthF(std::max(item_width_ * 0.02, 2.0));
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1,p2,p3,p4}}, Qt::WindingFill);
    auto item_name = name();

    if(item_name.empty())
    {
        return;
    }

    QFontMetricsF metrics (painter->font());
    auto width = metrics.width(item_name.data());
    auto height = metrics.height();
    auto center = QPointF (item_width_ / 2, (p1.y() + p4.y()) / 2);
    painter->drawText(QRectF (center - QPointF (width / 2, height / 2), QSizeF (width, height)), item_name.data());
}

information::information(item *parent)
    :fixed_item(parent)
 {
    set_attribute("信息名称");
    set_z_value(317);
    item_height_ /= small_object_height;
}

void information::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    item::mouseDoubleClickEvent (event);
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


