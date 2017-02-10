//#include "fetch_material.h"
//#include <QPointF>
//#include <QColor>
//#include <QPainter>
//#include <QStyleOptionGraphicsItem>
//#include <QPen>
//#include <QRectF>
/////取料

//namespace item {

//std::unique_ptr<fetch_material> fetch_material::make(QPointF pos, QColor color)
//{
//    std::unique_ptr<fetch_material>ret(new fetch_material);
//    ret->setPos(pos);
//    ret->set_color(std::move(color));
//    ret->type_ = "取料";
//    return ret;
//}

//fetch_material::fetch_material(item *parent)
//    :item(parent)
//{
//    item_width_ /= small_object_ratio;
//    item_height_ /= small_object_ratio;

//    set_z_value(203);
//}

//void fetch_material::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    auto the_pen = painter->pen();
//    the_pen.setColor(color());
//    the_pen.setWidthF(std::max(item_width_ * 0.02, 2.0));
//    painter->setPen(the_pen);

//    QPointF
//    p1 {0.75 * item_width_, 0.76 * item_height_},
//    p2 {0.82 * item_width_, 0.9 * item_height_},
//    p3 {0.86 * item_width_,0.65 * item_height_};

//    //给定坐标
//    painter->setBrush(Qt::white);

//    painter->drawArc(QRectF{0.1 * item_width_, 0, 0.8 * item_width_, item_height_}, 45 * 16, 270 * 16);
//    painter->setBrush(Qt::black);
//    painter->drawPolygon({{p1,p2,p3}},Qt::WindingFill);

//    item::paint(painter, option, widget);
//}

//}
