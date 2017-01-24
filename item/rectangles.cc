#include "rectangles.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
namespace item {


std::unique_ptr<rectangles>rectangles::make(QPointF pos, QColor color)
{
    std::unique_ptr <rectangles> ret(new rectangles);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

rectangles::rectangles(item* parent)
    :item(parent)
{

}

void rectangles::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "wecome paint";
     Q_UNUSED(widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(the_pen);
    painter->drawPolygon({{p1, p2, p4, p3}},Qt::WindingFill);
    painter->drawLine(p5,p6);
   item::paint(painter, option, widget);
  }
}
