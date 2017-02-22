#include "fixed_item.h"
#include <QPainter>
#include <QFontMetricsF>
#include <boost/algorithm/string.hpp>
#include <QStyleOptionGraphicsItem>

namespace item {

void fixed_item::paint_attribute(QPainter *painter) try
{
    QFontMetricsF metrix (painter->font ());
    auto height = metrix.height();

    auto bounding_rect = boundingRect ();
    QPointF start_point (bounding_rect.left (), bounding_rect.bottom ());

    int i = 0;
    for (auto& it : item_info_ ["attribute"])
    {
        if (!it.is_object() or it.empty())
        {
            continue;
        }

        std::string key = it.begin ().key();
        std::string value = it.begin ().value();
        boost::trim (value);

        if (value.empty())
        {
            continue;
        }

        QString paint_str = (key + " : " + value).data();
        auto width = metrix.width(paint_str);

        QRectF text_rect (start_point + QPointF (0, i * height), QSizeF (width, height));
        painter->drawText(text_rect, paint_str);
        ++i;
    }
}
catch (const std::exception & e)
{
    qDebug () << e.what ();
    return;
}

void paint(QPainter *painter, QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (widget);

    painter->setPen(Qt::black);

    if ((option->state bitand QStyle::State_Selected) and show_frame_)
    {
        set_dash(painter);
        painter->drawRect (boundingRect ());
    }

    paint_attribute(painter);
}

fixed_item::fixed_item(QGraphicsItem *parent)
    :item (parent)
{

}


} // namespace item
