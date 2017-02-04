#include "information.h"
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
///长方形
/// 修改完成
namespace item {

std::unique_ptr<information> information::make(QPointF pos, QColor color)
{
    std::unique_ptr<information>ret(new information);
    ret->setPos(pos);
    ret->set_color( std::move (color));
    ret->type_ = "信息";
    return ret;

}

void information::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QPointF
    p1_{0.01 * item_width, 0.0125 * item_height },
    p2_{0.99 * item_width, 0.0125 * item_height},
    p3_{ 0.01 * item_width, 0.9875 * item_height},
    p4_{ 0.99 * item_width, 0.9875 * item_height};

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_,p2_,p4_,p3_}},Qt::WindingFill);

    item::paint(painter, option, widget);
}

information::information(item *parent)
    :item(parent)
 {
 }

}


