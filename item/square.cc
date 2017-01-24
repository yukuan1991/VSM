#include "square.h"
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
///长方形
namespace item {


std::unique_ptr<square> square::make(QPointF pos, QColor color)
{
    std::unique_ptr<square>ret(new square);
    ret->setPos(pos);
    ret->set_color( std::move (color));
    return ret;

}

void square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "wecome paint";
     Q_UNUSED(widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(the_pen);
    painter->drawRect(((item_width-square_length)/2),((item_height-square_heigth)/2),square_length,square_heigth);//这里面给一个长和宽
   item::paint(painter, option, widget);
}

square::square(item *parent)
    :item(parent)
 {
 }

}


