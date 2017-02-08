#include "material_fetch_watch_board.h"
#include <QPointF>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QRectF>
///取料看板
  ///修改完成
  /// item_width 修改成了1/4
namespace item {


std::unique_ptr<material_fetch_watch_board> material_fetch_watch_board::make(QPointF pos, QColor color)
{
    std::unique_ptr<material_fetch_watch_board>ret(new material_fetch_watch_board);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "取料看板";
    return ret;
}

material_fetch_watch_board::material_fetch_watch_board(item *parent)
    :item(parent)
{
    set_attribute("产品种类");
    set_attribute("产品数量");
    set_attribute("取货地点");
    item_width_ /= width_heigth_small_;
    item_height_ /=width_heigth_small_;
}

void material_fetch_watch_board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPointF //shape1_, shape2_, shape3_, shape4_, shape5_;
    p1_{0.01 * item_width_,0.0125 * item_height_},
    p2_{0.25 * item_width_,0.0125 * item_height_},
    p3_{0.5 * item_width_,0.0125 * item_height_},
    p4_{0.74 * item_width_,0.0125 * item_height_},
    p5_{0.85 * item_width_,0.0125 * item_height_},
    p6_{0.95 * item_width_, 0.125 * item_height_},
    p7_{0.99 * item_width_,0.2 * item_height_},
    p8_{0.99 * item_width_,0.4875 * item_height_},
    p9_{0.99 * item_width_,0.9875 * item_height_},
    p10_{0.74* item_width_,0.9875 * item_height_},
    p11_{0.50 * item_width_,0.9875 * item_height_},
    p12_{0.25 * item_width_,0.9875 * item_height_},
    p13_{0.01 * item_width_,0.9875 * item_height_},
    p14_{0.01 * item_width_, 0.4875 * item_height_};


    auto the_pen = painter->pen();
    the_pen.setColor(color());
    the_pen.setWidthF(std::max(item_width_ * 0.02, 2.0));
    painter->setPen(the_pen);

    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_, p5_, p7_, p9_, p13_}},Qt::WindingFill);
    painter->drawLine(p14_,p2_);
    painter->drawLine(p13_,p3_);
    painter->drawLine(p12_,p4_);
    painter->drawLine(p11_,p6_);
    painter->drawLine(p10_,p8_);
    item::paint(painter, option, widget);
}
}
