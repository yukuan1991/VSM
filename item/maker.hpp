#pragma once
#include "item/item.h"
#include <memory>
#include "utility/raii.hpp"
#include <QDebug>
#include "item/board_station.h"
#include "item/board_arrival.h"
#include "item/operating_personnel.h"

namespace item
<%

using constructor = std::unique_ptr<item> (*) (item* parent);

inline QHash<QByteArray, constructor>& constructors ()
{
    static QHash<QByteArray, constructor> instance;
    return instance;
}


template<typename T>
void regester_class (QByteArray classname)
{
    constructors().insert(::move (classname), [] (item* parent){return std::make_unique<T> (new T (parent)); });
}

inline std::unique_ptr<item> make_item (const QString& classname, QPointF pos)
{
    using up_item = std::unique_ptr<item>;
    using item_maker = up_item (*) (QPointF);


    static std::map<QString, item_maker> type_map
    {
        {"看板以批量方式传达", [] (QPointF p)->up_item { return board_arrival::make (p, Qt::black); }},
        //{"生产工序", production_sequence_maker},
        //{"其他公司", other_company_maker},
        //{"数据箱", data_box_maker},
        //{"库存", storage_maker},
        //{"卡车运输", truck_transport_maker},
        //{"库存超市", storage_super_market_maker},
        //{"信息", information_maker},
        //{"生产看板", production_watcher_board_maker},
        //{"取料看板", material_fetch_watch_board_maker},
        //{"信号看板", signal_board_maker},
        //{"顺序拉动球", sequence_pull_ball_maker},
        //{"看板以批量方式传达", board_arrival_maker},
        //{"均衡生产", balanced_production_maker},
        //{"现场调度", adjustment_on_scene_maker},
        //{"改善", improvement_maker},
        //{"取料", fetch_material_maker},
        //{"缓冲或安全库存", cache_or_safe_storage_maker},
        {"操作员", [] (QPointF p)->up_item { return operating_personnel::make (p, Qt::black); }}
    };

    auto found = type_map.find(classname);
    if (found == type_map.end() or found->second == nullptr)
    {
        return nullptr;
    }

    return (found->second) (pos);
}

inline std::unique_ptr<item> make_arrow (const QString& name, QPointF start, QPointF end)
{
    if (name == "传统信息流")
    {

    }
    else if (name == "电子信息流")
    {

    }
    else if (name == "物流")
    {

    }

    return nullptr;
}


%>
