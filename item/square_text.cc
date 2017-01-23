#include "square_text.h"
#include <QDebug>
namespace item {


std::unique_ptr<square_text> square_text::make(QPointF pos, QColor color)
{
    qDebug()<< "wecome make";
   std::unique_ptr<square_text>ret(new square_text);
   ret->setPos(pos);
   ret->set_color( std::move (color));
   return ret;
}

square_text::square_text(item* parent)
    :item(parent)
{



}

void square_text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "wecome paint";
     Q_UNUSED(widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(the_pen);
    painter->drawRect(((item_width-square_length)/2),((item_height-square_heigth)/2),square_length,square_heigth);//这里面给一个长和宽
    QRectF text_rect {(square_length - text_square_length)/2 +10,
                 (square_heigth - text_square_heigth) / 2 +20, text_square_length, text_square_heigth};
    painter->drawText(text_rect,"OXOX", Qt::AlignVCenter | Qt::AlignCenter);

    if (option->state bitand QStyle::State_Selected)
    {
        qDebug()<<"长方形被选中";
        painter->setBrush(Qt::transparent);
        QPen pen;
        pen.setColor(Qt::black);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }
  }
}
