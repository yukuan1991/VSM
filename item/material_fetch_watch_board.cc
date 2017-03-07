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


bool material_fetch_watch_board::init()
{
    set_item_type("取料看板");

    enable_attribute ("产品种类");
    enable_attribute ("产品数量");
    enable_attribute ("取货地点");

    set_z_value(314);

    return true;

}

std::unique_ptr<material_fetch_watch_board> material_fetch_watch_board::make(json data, QPointF pos, abstract_item* parent)
{
    std::unique_ptr<material_fetch_watch_board>ret(new material_fetch_watch_board(::move(data), pos, parent));
    if(!ret->init ())
    {
        return  nullptr;
    }
    else
    {
        return ret;
    }
}

material_fetch_watch_board::material_fetch_watch_board(json data, QPointF pos,abstract_item *parent)
    :fixed_item(::move(data), pos, parent)
{
}

void material_fetch_watch_board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto item_width = width();
    auto item_height = height();
    QPointF //shape1_, shape2_, shape3_, shape4_, shape5_;
    p1_{0.01 * item_width,0.0125 * item_height},
    p2_{0.25 * item_width,0.0125 * item_height},
    p3_{0.5 * item_width,0.0125 * item_height},
    p4_{0.74 * item_width,0.0125 * item_height},
    p5_{0.85 * item_width,0.0125 * item_height},
    p6_{0.95 * item_width, 0.125 * item_height},
    p7_{0.99 * item_width,0.2 * item_height},
    p8_{0.99 * item_width,0.4875 * item_height},
    p9_{0.99 * item_width,0.9875 * item_height},
    p10_{0.74* item_width,0.9875 * item_height},
    p11_{0.50 * item_width,0.9875 * item_height},
    p12_{0.25 * item_width,0.9875 * item_height},
    p13_{0.01 * item_width,0.9875 * item_height},
    p14_{0.01 * item_width, 0.4875 * item_height};


    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(std::max(item_width * 0.02, 2.0));
    painter->setPen(the_pen);

    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_, p5_, p7_, p9_, p13_}},Qt::WindingFill);
    painter->drawLine(p14_,p2_);
    painter->drawLine(p13_,p3_);
    painter->drawLine(p12_,p4_);
    painter->drawLine(p11_,p6_);
    painter->drawLine(p10_,p8_);
    fixed_item::paint(painter, option, widget);
}
}
