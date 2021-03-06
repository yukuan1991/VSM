﻿#include "abstract_item.h"
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QDebug>
#include <boost/algorithm/string.hpp>
#include "item/balanced_production.h"
#include "item/board_arrival.h"
#include "item/adjustment_on_scene.h"
#include "item/board_info_flow.h"
#include "item/other_company.h"
#include "item/board_station.h"
#include "item/cache_or_safe_storage.h"
#include "item/fetch_material.h"
#include "item/improvement.h"
#include "item/information.h"
#include "item/material_fetch_watch_board.h"
#include "item/operating_personnel.h"
#include "item/other_company.h"
#include "item/product_to_customer.h"
#include "item/production_control_department.h"
#include "item/production_sequence.h"
#include "item/production_watcher_board.h"
#include "item/sequence_pull_ball.h"
#include "item/signal_board.h"
#include "item/storage.h"
#include "item/storage_super_market.h"
#include "item/truck_transport.h"
#include <assert.h>
#include "item/value_added_radtio.h"
#include "item/material_flow.h"
#include "item/traditional_info_flow.h"
#include "item/electric_info_flow.h"
#include "item/product_to_customer.h"
#include "item/fifo.h"
#include "item/text_item.h"
#include <QGraphicsScene>

namespace item
<%
using namespace std;

nlohmann::json abstract_item::dump_scene(not_null<QGraphicsScene *> scene)
{
    const auto list_item = scene->items ();
    json json_items;
    for (auto it : list_item)
    {
        auto casted_item = dynamic_cast<abstract_item*> (it);
        if (casted_item == nullptr)
        {
            continue;
        }

        const auto pos = casted_item->pos ();

        json json_pos {{"x", pos.x ()}, {"y", pos.y ()}};
        json_items.push_back ({{"pos", ::move (json_pos)}, {"detail", casted_item->dump ()}});
    }
    return json_items;
}

const json & abstract_item::json_find(const json &data, const string &key)
{
    auto found = data.find (key);
    if (found == end (data))
    {
        throw std::logic_error ("cannot find key in json");
    }

    return *found;
}

void abstract_item::set_attribute(string_view key, string value) try
{
    auto& attribute = item_info_ ["attribute"];
    if (!attribute.is_array())
    {
        attribute = json::array ();
        attribute.push_back({{key.to_string (), value}});
        return;
    }

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
catch (const std::exception& e)
{
    qDebug () << __PRETTY_FUNCTION__ << " " << e.what();
    return;
}

void abstract_item::enable_attribute(string_view key) try
{
    auto& attribute = item_info_ ["attribute"];
    if (!attribute.is_array())
    {
        attribute = json::array ();
        attribute.push_back({{key.to_string (), ""}});
        return;
    }

    for (auto & it : attribute)
    {
        if (!it.is_object() or it.empty())
        {
            continue;
        }

        std::string current_key = it.begin().key();
        if (key == current_key)
        {
            return;
        }
    }

    attribute.push_back({{key.to_string (), ""}});
}
catch (const std::exception & )
{
    return;
}

abstract_item::abstract_item(nlohmann::json data, QPointF pos, abstract_item *parent)
    :abstract_item (parent)
{
    item_info_ = ::move (data);
    setPos (pos);
}

abstract_item::abstract_item(QGraphicsItem *parent) : QGraphicsObject (parent)
{
    setFlags (ItemIsSelectable | ItemIsMovable);
}

using up_item = unique_ptr<abstract_item>;
using generator = up_item (*) (json, QPointF, abstract_item*);

unique_ptr<abstract_item> abstract_item::make(json full_data, abstract_item *parent) try
{
    const string type = full_data ["detail"]["type"];
    qreal x = full_data ["pos"]["x"];
    qreal y = full_data ["pos"]["y"];
    auto & data = full_data ["detail"];

    QPointF pos (x, y);

    if (type == "生产工序")
    {
        return production_sequence::make(::move (data), pos, parent);
    }
    else if (type == "库存")
    {
        return storage::make(::move (data), pos, parent);

    }
    else if(type == "卡车运输")
    {
        return truck_transport::make(::move (data), pos, parent);
    }
    else if(type == "库存超市")
    {
        return storage_super_market::make(::move (data), pos, parent);
    }
    else if(type == "看板以批量方式传达")
    {
         return board_arrival::make(::move (data), pos, parent);
    }
    else if(type == "其他公司")
    {
        return other_company::make(::move(data), pos, parent);
    }
    else if(type == "信息")
    {
        return information::make(::move(data), pos, parent);
    }
    else if(type == "生产看板")
    {
        return production_watcher_board::make(::move(data), pos, parent);
    }
    else if(type == "取料看板")
    {
        return material_fetch_watch_board ::make(::move(data), pos, parent);
    }
    else if(type == "信号看板")
    {
        return signal_board ::make(::move(data), pos, parent);
    }
    else if(type == "顺序拉动球")
    {
        return sequence_pull_ball::make(::move(data), pos, parent);
    }
    else if(type == "均衡生产")
    {
        return balanced_production::make(::move(data), pos, parent);
    }
    else if(type == "现场调度")
    {
        return adjustment_on_scene::make(::move(data), pos, parent);
    }
    else if(type == "改善")
    {
        return improvement::make(::move(data), pos, parent);
    }
    else if(type == "取料")
    {
        return fetch_material ::make(::move(data), pos, parent);
    }
    else if(type == "缓冲或安全库存")
    {
        return cache_or_safe_storage ::make(::move(data), pos, parent);
    }
    else if(type == "操作员")
    {
        return operating_personnel::make(::move(data), pos, parent);
    }
    else if(type == "看板站")
    {
        return board_station::make(::move(data), pos, parent);
    }
    else if(type == "生产控制部门")
    {
        return production_control_department::make(::move(data), pos, parent);
    }
    else if(type == "增值比")
    {
        return value_added_radtio::make(::move(data), pos, parent);
    }
    else if (type == "物流")
    {
        return material_flow::make (::move (data), pos, parent);
    }
    else if (type == "传统信息流")
    {
        return traditional_info_flow::make (::move (data), pos, parent);
    }
    else if (type == "电子信息流")
    {
        return electric_info_flow::make (::move (data), pos, parent);
    }
    else if (type == "成品发送至顾客")
    {
        return product_to_customer::make(::move (data), pos, parent);
    }
    else if (type == "先进先出")
    {
        return fifo::make (::move (data), pos, parent);
    }
    else if (type == "看板用信息流")
    {
        return board_info_flow::make (::move (data), pos, parent);
    }
    else if (type == "文字")
    {
        return text_item::make (::move (data), pos, parent);
    }
    assert (false);
    return nullptr;
}
catch (const std::exception & e)
{
    return nullptr;
}

string abstract_item::name()
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

string abstract_item::item_type() const noexcept
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

void abstract_item::set_item_type(const string &type)
{
    item_info_ ["type"] = type;
}

string abstract_item::attribute(const string &key) try
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

void abstract_item::apply_z_value(selected_item yes_or_no)
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


QVariant abstract_item::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

string abstract_item::find_json_value(const string& key, const json& data)
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
