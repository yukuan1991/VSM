#include "item.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>

namespace item
<%

item::item(QObject *parent) : QObject(parent)
{
    setFlags (ItemIsSelectable | ItemIsMovable);
    //auto arr = nlohmann::json::array({{"123, 456"}, {"456", "789"}});
    set_data({{{"123", "456"}}, {{"456", "789"}}});
}

void item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    try
    {
        if (option->state bitand QStyle::State_Selected)
        {
            set_dash(painter);
            painter->drawRect (boundingRect ());
        }

        QFontMetricsF metrix (painter->font ());
        auto height = metrix.height();
        auto h_scale = metrix.height ();
        QString qstr = {};
        qDebug () << item_info_.size ();

        int i = 0;
        auto bounding_rect = boundingRect ();
        QPointF start_point (bounding_rect.left (), bounding_rect.bottom ());
        for (auto& it : item_info_)
        {
            SCOPE_EXIT { i ++; };
            std::string key = it.begin ().key();
            std::string value = it.begin ().value();
            QString paint_str = (key + " : " + value).data();
            auto width = metrix.width(paint_str);

            QRectF text_rect (start_point + QPointF (0, i * height), QSizeF (width, height));
            painter->drawText(text_rect, paint_str);
        }
    }
    catch (const std::exception& e)
    {
        qDebug () << "error:" << e.what();
    }
}

QRectF item::boundingRect() const
{
    return {0, 0, item_width, item_height};
}

void item::set_dash(QPainter *painter)
{
    painter->setBrush(Qt::transparent);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
}

%> // namespace item
