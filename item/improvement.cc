#include "improvement.h"
#include <QPointF>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QRectF>
///改善
///修改完成
namespace item {


std::unique_ptr<improvement> improvement::make(QPointF pos, QColor color)
{
    std::unique_ptr<improvement>ret(new improvement);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "改善";
    return ret;
}

improvement::improvement(item *parent)
    :item(parent)
{


}

void improvement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto x_scale = item_width / 100;
    auto y_scale = item_height / 80;
    QPointF
    p1 {0.01 * item_width,0.1 * item_height},p2 {0.33 * item_width,0.2875 * item_height},
    p3 {0.38 * item_width,0.125 * item_height} ,p4 {0.49 * item_width,0.2625 * item_height},
    p5 {0.65 * item_width,0.0125 * item_height}, p6 {0.64 * item_width,0.2375 * item_height},
    p7 {0.82 * item_width,0.2125 * item_height},p8 {0.76 * item_width,0.325 * item_height},
    p9 {0.93* item_width,0.375 * item_height},p10 {0.83 * item_width,0.4625 * item_height},
    p11 {0.97 * item_width,0.6 * item_height},p12 {0.77 * item_width,0.5875 * item_height},
    p13 {0.8 * item_width,0.775 *item_height}, p14 {0.64 * item_width,0.6625 * item_height},
    p15 {0.59 * item_width,0.85 * item_height},p16 {0.48 * item_width,0.6875 * item_height},
    p17 {0.39* item_width,0.925 *item_height},p18 {0.35 * item_width, 0.7125 * item_height},
    p19 {0.22 * item_width,0.775 * item_height},p20 {0.25 * item_height,0.6375 * item_height},
    p21 {0.01 * item_width,52 * y_scale},p22 {17 * x_scale, 42 * y_scale},
    p23 {1 * x_scale,31 * y_scale},p24 {20 * x_scale, 27 * y_scale};

    auto the_pen = painter->pen();
    the_pen.setWidthF(item_width * 0.02);
    the_pen.setColor(color());
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24}},Qt::WindingFill);

    item::paint(painter, option, widget);
}

}
