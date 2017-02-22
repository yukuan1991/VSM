#include "item.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <boost/algorithm/string.hpp>
#include <algorithm>

namespace item
<%
using namespace std;

nlohmann::json item::dump_scene(not_null<QGraphicsScene *> scene)
{
    return {};
}

void item::set_attribute(string_view key, string value) try
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

item::item(nlohmann::json data, QPointF pos, item *parent)
    :item (parent)
{
    item_info_ = ::move (data);
    setPos (pos);
}

item::item(QGraphicsItem *parent) : QGraphicsObject (parent)
{
    setFlags (ItemIsSelectable | ItemIsMovable);
}

using up_item = unique_ptr<item>;
using generator = up_item (*) (json, QPointF, item*);
const map<string, generator> item_map
{
    {"看板以批量方式传达", [] ((json j, QPointF p, item* o))->up_item { return board_arrival::make (::move (j), p, o); }},
    {"生产工序", [] ((json j, QPointF p, item* o))->up_item { return production_sequence::make(::move (j), p, o); }},
    { "其他公司",[] ((json j, QPointF p, item* o))->up_item { return other_company::make(::move (j), p, o); }},
    //{"数据箱", [] ((json j, QPointF p, item* o))->up_item { return data_box::make(p, Qt::black); }},
    {"库存", [] ((json j, QPointF p, item* o))->up_item { return storage::make(::move (j), p, o); }},
    {"卡车运输", [] ((json j, QPointF p, item* o))->up_item { return truck_transport::make(::move (j), p, o); }},
    {"库存超市", [] ((json j, QPointF p, item* o))->up_item { return storage_super_market::make(::move (j), p, o); }},
    {"信息", [] ((json j, QPointF p, item* o))->up_item { return information::make(::move (j), p, o); }},
    {"生产看板",  [] ((json j, QPointF p, item* o))->up_item { return production_watcher_board::make(::move (j), p, o); }},
    {"取料看板",  [] ((json j, QPointF p, item* o))->up_item { return material_fetch_watch_board::make(::move (j), p, o); }},
    {"信号看板",  [] ((json j, QPointF p, item* o))->up_item { return signal_board::make(::move (j), p, o); }},
    {"顺序拉动球",  [] ((json j, QPointF p, item* o))->up_item { return sequence_pull_ball::make(::move (j), p, o); }},
    {"看板以批量方式传达",  [] ((json j, QPointF p, item* o))->up_item { return board_arrival::make(::move (j), p, o); }},
    {"均衡生产",  [] ((json j, QPointF p, item* o))->up_item { return balanced_production::make(::move (j), p, o); }},
    {"现场调度",  [] ((json j, QPointF p, item* o))->up_item { return adjustment_on_scene::make(::move (j), p, o); }},
    {"改善",  [] ((json j, QPointF p, item* o))->up_item { return improvement::make(::move (j), p, o); }},
    {"取料",  [] ((json j, QPointF p, item* o))->up_item { return fetch_material::make(::move (j), p, o); }},
    {"缓冲或安全库存",  [] ((json j, QPointF p, item* o))->up_item { return cache_or_safe_storage::make(::move (j), p, o); }},
    {"操作员", [] ((json j, QPointF p, item* o))->up_item { return operating_personnel::make (::move (j), p, o); }},
    {"看板站", [] ((json j, QPointF p, item* o))->up_item { return board_station::make (::move (j), p, o); }},
    {"生产控制部门", [] ((json j, QPointF p, item* o))->up_item { return production_control_department::make (::move (j), p, o); }},
    {"增值比", [] ((json j, QPointF p, item* o))->up_item { return value_added_radtio::make(::move (j), p, o);}},
};

unique_ptr<item> item::make(json data, QPointF pos, item *parent) try
{
    auto type = data ["type"];
    auto found = item_map.find (type);
    if (found == end (item_map))
    {
        return nullptr;
    }

    if (found->second == nullptr)
    {
        return nullptr;
    }

    return (found->second) (::move (data), pos, parent);
}
catch (const std::exception & e)
{
    return nullptr;
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

string item::find_json_value(const string& key, const json& data)
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
