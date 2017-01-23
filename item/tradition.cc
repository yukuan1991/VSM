//#include "vs_item_tradition.h"
//#include <memory>
//#include <QStyleOptionGraphicsItem>
//#include <QCOlor>
//#include <QPainter>
//vs_item_tradition::vs_item_tradition(vs_item* parent)
//    :vs_item(parent)
//{

//}

//std::unique_ptr<vs_item_tradition> vs_item_tradition::make(QPointF pos, QColor color)
//{
//    std::unique_ptr <vs_item_electron> ret(new vs_item_electron);
//    ret->setPos(pos);
//    ret->set_color(std::move(color));
//    return ret;
//}

//void vs_item_tradition::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    auto the_pen = painter->pen();
//    the_pen.setColor(color());
//    painter->setPen(the_pen);
//    //给定坐标
//    painter->setBrush(Qt::white);
//    painter->drawLine(p1,p2);
//    painter->drawLine(p3,p5);
//    painter->drawLine(p3,p4);
//    painter->drawLine(p5,p4);


//    if(option->state bitand QStyle::State_Selected)
//    {
//        painter->setBrush(Qt::transparent);//画刷为空白
//        QPen pen;
//        pen.setColor(Qt::black);
//        pen.setStyle(Qt::DashLine);
//        painter->setPen(pen);
//        painter->drawRect(boundingRect ());
//    }


//}
