#include "operating_personnel.h"
#include <memory>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
///修改好
/// 修改好1/4
namespace item
{

std::unique_ptr<operating_personnel> operating_personnel::make(json data, QPointF pos, abstract_item* parent)
{
    std::unique_ptr<operating_personnel> ret(new operating_personnel(::move(data), pos, parent));

    if(!ret->init ())
    {
        return nullptr;
    }
    else
    {
       return ret;
    }
}

bool operating_personnel::init()
{
     set_item_type("操作员");
     enable_attribute ("操作员数量");

     set_z_value(309);

     return true;

}

operating_personnel::operating_personnel(json data, QPointF pos, abstract_item* parent)
    :fixed_item (::move(data), pos, parent)
{

}

void operating_personnel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);
    auto item_width = width();
    auto item_height = height();
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(std::max(0.02 * item_width,2.0));
    painter->setPen(the_pen);

    painter->drawArc(QRectF{0.1 * item_width, item_height * 10 / 80, 0.8 * item_width, item_height * 60 / 80}, 180 * 16, 180 * 16);
    painter->setBrush(Qt::white);
    painter->drawEllipse (QRectF(0.3 * item_width, item_height * 20 / 80, 0.4 * item_width, item_height * 40 / 80));

    fixed_item::paint(painter, option, widget);
}
}
