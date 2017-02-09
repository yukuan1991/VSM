#include "production_watcher_board.h"
#include <QPainter>
#include <QLineF>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
///修改完成
/// 修改成1/4
namespace item {


production_watcher_board::production_watcher_board(item *parent)
    :item(parent)
{
    set_attribute("产品种类");
    set_attribute("生产数量");
    set_attribute("需求地点");
    set_attribute("供货时间");

    set_z_value(313);

    item_width_ /= small_object_ratio;
    item_height_ /= small_object_ratio;

}
std::unique_ptr<production_watcher_board> production_watcher_board::make(QPointF pos, QColor color)
{
    std::unique_ptr<production_watcher_board> ret(new production_watcher_board);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "生产看板";
    return ret;
}

void production_watcher_board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF
    p1_ {0.01 * item_width_, 0.0125 * item_height_},
    p2_ {0.85 * item_width_, 0.0125 * item_height_},
    p3_ {0.99 * item_width_, 0.2 * item_height_},
    p4_ {0.99 * item_width_, 0.9875 * item_height_},
    p5_ {0.01 * item_width_, 0.9875 * item_height_};

    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(std::max(item_width_ * 0.02 , 2.0));
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_, p2_, p3_,p4_,p5_}}, Qt::WindingFill);

    item::paint(painter, option, widget);
 }
}
