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
    p1{0.01 * item_width_, 0.0125 * item_height_ },
    p2{0.99 * item_width_, 0.0125 * item_height_},
    p3{ 0.01 * item_width_, 0.9875 * item_height_},
    p4{ 0.99 * item_width_, 0.9875 * item_height_};

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidthF(item_width_ * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1,p2,p4,p3}},Qt::WindingFill);

    item::paint(painter, option, widget);
}

information::information(item *parent)
    :item(parent)
 {
    set_attribute("信息名称");
 }

}


