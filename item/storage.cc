#include "storage.h"
#include "QPainter"
#include "QStyleOptionGraphicsItem"
#include "QWidget"
///修改成了item_width * 1/2
namespace item {


std::unique_ptr<storage> storage::make(json data, QPointF pos, item* parent)
{
    std::unique_ptr <storage> ret(new storage(::move(data),pos, parent));
    if(!ret->init ())
    {
        return nullptr;
    }
    else
    {
        return ret;
    }
}


storage::storage(json data, QPointF pos, item* parent)
    :fixed_item(::move(data), pos, parent)
{

}

bool storage::init()
{

    set_attribute("库存数量");
    set_attribute("库存天数");
    set_attribute("材料名");

    set_item_type("库存");

    set_z_value(303);

    return true;


}

void storage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(std::max(item_width_ * 0.02, 2.0));
    painter->setPen(the_pen);

    auto x_scale = width() / 100;
    auto y_scale = height() / 80;
    QPointF p1{x_scale * 49, y_scale * 1},
    p2{x_scale * 99, y_scale * 79},
    p3{x_scale * 1, y_scale * 79};


    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1,p2,p3}},Qt::WindingFill);
//    painter->drawLine (QPointF {x_scale * 49, y_scale * 1}, {x_scale * 99, y_scale * 79});
//    painter->drawLine (QPointF {x_scale * 1, y_scale * 79}, {x_scale * 99, y_scale * 79});
//    painter->drawLine (QPointF {x_scale * 1,y_scale * 79}, {x_scale * 49, y_scale * 1});
    QFont font;
    font.setPointSizeF (item_width_ / 5);
    QFontMetricsF metrics (font);
    auto text_height = metrics.height();
    auto text_width = metrics.width("I");
    QRectF text_rect {x_scale * 49-text_width/2,y_scale * 40,text_width,text_height};
    painter->setFont(font);
    painter->drawText(text_rect, "I", Qt::AlignVCenter | Qt::AlignCenter);

    item::paint (painter, option, widget);
}
}
