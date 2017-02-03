#include "information.h"
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
///长方形
namespace item {


std::unique_ptr<information> information::make(QPointF pos, QColor color)
{
    std::unique_ptr<information>ret(new information);
    ret->setPos(pos);
    ret->set_color( std::move (color));
    return ret;

}

void information::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "wecome paint";
     Q_UNUSED(widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(the_pen);
    painter->drawRect(((item_width-information_length)/2),((item_height-information_heigth)/2),information_length,information_heigth);//这里面给一个长和宽
   item::paint(painter, option, widget);
}

information::information(item *parent)
    :item(parent)
 {
 }

}


