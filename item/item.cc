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
    set_data({{{"测试属性1", " 测试属性1的值"}},
              {{"测试属性2", "测试属性2的值"}},
              {{"测试属性3", "测试属性3的值"}},
              {{"测试属性4", ""}}
             });
}

void item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    if (option->state bitand QStyle::State_Selected)
    {
        set_dash(painter);
        painter->drawRect (boundingRect ());
    }

    paint_attribute(painter);

}

void item::paint_attribute(QPainter *painter) try
{
    QFontMetricsF metrix (painter->font ());
    auto height = metrix.height();
    auto h_scale = metrix.height ();
    QString qstr = {};

    auto bounding_rect = boundingRect ();
    QPointF start_point (bounding_rect.left (), bounding_rect.bottom ());

    int i = 0;
    for (auto& it : item_info_)
    {
        std::string key = it.begin ().key();
        std::string value = it.begin ().value();
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
catch (const std::exception& e)
{
    qDebug () << e.what ();
}

QRectF item::boundingRect() const
{
    return {0, 0, item_width, item_height};
}

void item::set_dash(QPainter *painter)
{
    painter->setBrush(Qt::transparent);
    QPen pen;
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
}

%> // namespace item
