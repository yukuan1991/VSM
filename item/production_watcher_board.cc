#include "production_watcher_board.h"
#include <QPainter>
#include <QLineF>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
namespace item {


production_watcher_board::production_watcher_board(item *parent)
    :item(parent)
{

}
std::unique_ptr<production_watcher_board> production_watcher_board::make(QPointF pos, QColor color)
{
    qDebug() << "make";
    std::unique_ptr<production_watcher_board> ret(new production_watcher_board);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    return ret;
}

void production_watcher_board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    painter->setPen(the_pen);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1, p2, p3,p4,p5}}, Qt::WindingFill);
    item::paint(painter, option, widget);
 }

}
