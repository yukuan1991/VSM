#include "production_watcher_board.h"
#include <QPainter>
#include <QLineF>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
///修改完成
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
    ret->type_ = "生产看板";
    return ret;
}

void production_watcher_board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_, p2_, p3_,p4_,p5_}}, Qt::WindingFill);

    item::paint(painter, option, widget);
 }
}
