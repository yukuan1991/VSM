﻿#include "item.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <boost/algorithm/string.hpp>
#include <algorithm>

namespace item
<%
using namespace std;

item::item(QGraphicsItem *parent) : QGraphicsObject (parent)
{
    setFlags (ItemIsSelectable | ItemIsMovable);
}


string item::name()
{
    auto iter = item_info_.find("name");
    if (iter != item_info_.end () and iter->is_string ())
    {
        return *iter;
    }
    else
    {
        return {};
    }
}

string item::item_type() const noexcept
{
    auto found = item_info_.find ("type");
    if (found == end (item_info_) or !found->is_string ())
    {
        return {};
    }
    else
    {
        return *found;
    }
}

void item::set_item_type(const string &type)
{
    item_info_ ["type"] = type;
}

void item::set_attribute(string_view key, std::string value)
{
    auto& attribute = item_info_ ["attribute"];
    for (auto & it : attribute)
    {
        if (!it.is_object() or it.empty())
        {
            continue;
        }

        std::string current_key = it.begin().key();
        if (key == current_key)
        {
            auto& target = *(it.begin());
            target = value;
            return;
        }
    }

    attribute.push_back({{key.to_string (), value}});
}

string item::attribute(const string &key) try
{
    auto& attribute = item_info_ ["attribute"];

    for (auto & it : attribute)
    {
        if (!it.is_object() or it.empty())
        {
            continue;
        }

        std::string current_key = it.begin().key();
        if (key == current_key)
        {
            string value = it.begin().value();
            return value;
        }
    }

    return {};
}
catch (std::exception const &)
{
    return {};
}

void item::apply_z_value(selected_item yes_or_no)
{
    if (yes_or_no == selected_item::yes)
    {
        setZValue (z_value_ + 0.5);
    }
    else
    {
        setZValue(z_value_);
    }
}

QRectF item::boundingRect() const
{
    return {0, 0, item_width_, item_height_};
}


void item::set_dash(QPainter *painter)
{
    painter->setBrush(Qt::transparent);
    QPen pen;
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
}

QVariant item::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        if (isSelected ())
        {
            set_z_value (z_value_ + 0.5);
        }
        else
        {
            set_z_value (z_value_);
        }
    }
    return QGraphicsItem::itemChange (change, value);
}

string item::find_json_value(const string& key, const nlohmann::json& data)
{
    auto iter = data.find(key);
    if (iter != data.end () and iter->is_string ())
    {
        return *iter;
    }
    else
    {
        return {};
    }

}

%> // namespace item
