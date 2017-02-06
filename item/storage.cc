#include "storage.h"
#include "QPainter"
#include "QStyleOptionGraphicsItem"
#include "QWidget"
namespace item {


std::unique_ptr<storage> storage::make(QPointF pos, QColor color)
{
    std::unique_ptr <storage> ret(new storage);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "库存";
    return ret;
}


storage::storage(item* parent)
    :item(parent)
{

}

void storage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    auto x_scale = item_width / 100;
    auto y_scale = item_height / 80;
    painter->drawLine (QPointF {x_scale * 49, y_scale * 1}, {x_scale * 99, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 79}, {x_scale * 99, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 79}, {x_scale * 49, y_scale * 1});
    QFont font;
    font.setPointSize(20);
    QFontMetricsF metrics (font);
    auto text_height = metrics.height();
    auto text_width = metrics.width("I");
    QRectF text_rect {x_scale * 49-text_width/2,y_scale * 40,text_width,text_height};
    painter->setFont(font);
    painter->drawText(text_rect, "I", Qt::AlignVCenter | Qt::AlignCenter);
}
}
