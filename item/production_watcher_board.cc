#include "production_watcher_board.h"
#include <QPainter>
#include <QLineF>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

namespace item {

production_watcher_board::production_watcher_board(json data, QPointF pos, item *parent)
    :fixed_item(::move(data), pos, parent)
{

}
std::unique_ptr<production_watcher_board> production_watcher_board::make(json data, QPointF pos, item* parent)
{
    std::unique_ptr<production_watcher_board> ret(new production_watcher_board(::move(data),pos, parent));
    if(!ret->init ())
    {
        return nullptr;
    }
    else
    {
        return ret;
    }
}

bool production_watcher_board::init()
{
     set_item_type("生产看板");


     set_attribute("产品种类");
     set_attribute("生产数量");
     set_attribute("需求地点");
     set_attribute("供货时间");

     set_z_value(313);

     return true;

}

void production_watcher_board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto item_width = width();
    auto item_height = height();
    QPointF
    p1_ {0.01 * item_width, 0.0125 * item_height},
    p2_ {0.85 * item_width, 0.0125 * item_height},
    p3_ {0.99 * item_width, 0.2 * item_height},
    p4_ {0.99 * item_width, 0.9875 * item_height},
    p5_ {0.01 * item_width, 0.9875 * item_height};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(std::max(item_width * 0.02 , 2.0));
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_, p2_, p3_,p4_,p5_}}, Qt::WindingFill);

    fixed_item::paint(painter, option, widget);
 }
}
