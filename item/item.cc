#include "item.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <algorithm>

namespace item
<%
using namespace std;

item::item(QObject *parent) : QObject(parent)
{
    setFlags (ItemIsSelectable | ItemIsMovable);
    set_attribute("123", "456");
    set_attribute("aaa", "bbb");
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
    QString qstr = {};

    auto bounding_rect = boundingRect ();
    QPointF start_point (bounding_rect.left (), bounding_rect.bottom ());

    int i = 0;
    for (auto& it : item_info_)
    {
        if (!it.is_object() or it.empty())
        {
            continue;
        }

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

void item::set_attribute(string_view key, std::string value)
{
    for (auto & it : item_info_)
    {
        if (!it.is_object() or it.empty())
        {
            continue;
        }

        std::string current_key = it.begin().key();
        if (key == current_key)
        {
            auto target = *(it.begin());
            target = value;
            return;
        }
    }

    item_info_.push_back({{key.to_string (), value}});
}

void item::apply_z_value(selected_item yes_or_no)
{
    if (yes_or_no == selected_item::yes)
    {

    }
}

optional<std::string> item::attribute(string_view key) try
{
    auto it = find_if (item_info_.begin (), item_info_.end (), [&] (auto&& it)
    {
        if (!it.is_object () or it.empty ())
        {
            return false;
        }

        std::string current_key = it.begin ().key ();
        if (current_key == key)
        {
            return true;
        }
        else
        {
            return false;
        }
    });

    if (it != item_info_.end ())
    {
        return it->begin().value();
    }

    return nullopt;
}
catch (std::exception const &)
{
    return nullopt;
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
