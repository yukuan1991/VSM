#pragma once
#include "item/item.h"
#include <memory>
#include "utility/raii.hpp"
#include <QDebug>
#include "item/board_station.h"
#include "item/board_arrival.h"
#include "item/operating_personnel.h"
#include "item/production_sequence.h"
#include "item/data_box.h"
#include "item/storage_super_market.h"
#include "item/information.h"
#include "item/production_watcher_board.h"
#include "item/material_fetch_watch_board.h"
#include "item/signal_board.h"
#include "item/sequence_pull_ball.h"
#include "item/balanced_production.h"
#include "item/board_arrival.h"
#include "item/adjustment_on_scene.h"
#include "item/improvement.h"
#include "item/cache_or_safe_storage.h"
#include "item/fetch_material.h"
#include "item/storage.h"
#include "item/truck_transport.h"
#include "item/other_company.h"
#include "item/material_flow.h"
#include "item/electric_info_flow.h"
#include "item/product_to_customer.h"
#include "traditional_info_flow.h"
#include "production_control_department.h"
#include "value_added_radtio.h"
#include "item/fifo.h"


namespace item
<%

using constructor = std::unique_ptr<item> (*) (item* parent);


inline std::unique_ptr<item> make_item (const QString& classname, QPointF pos)
{
    using up_item = std::unique_ptr<item>;
    using item_maker = up_item (*) (QPointF);


    static std::map<QString, item_maker> type_map
    {
        {"看板以批量方式传达", [] (QPointF p)->up_item { return board_arrival::make (p, Qt::black); }},
        {"生产工序", [] (QPointF p)->up_item { return production_sequence::make(p, Qt::black); }},
        { "其他公司",[] (QPointF p)->up_item { return other_company::make(p, Qt::black); }},
        {"数据箱", [] (QPointF p)->up_item { return data_box::make(p, Qt::black); }},
        {"库存", [] (QPointF p)->up_item { return storage::make(p, Qt::black); }},
        {"卡车运输", [] (QPointF p)->up_item { return truck_transport::make(p, Qt::black); }},
        {"库存超市", [] (QPointF p)->up_item { return storage_super_market::make(p, Qt::black); }},
        {"信息", [] (QPointF p)->up_item { return information::make(p, Qt::black); }},
        {"生产看板",  [] (QPointF p)->up_item { return production_watcher_board::make(p, Qt::black); }},
        {"取料看板",  [] (QPointF p)->up_item { return material_fetch_watch_board::make(p, Qt::black); }},
        {"信号看板",  [] (QPointF p)->up_item { return signal_board::make(p, Qt::black); }},
        {"顺序拉动球",  [] (QPointF p)->up_item { return sequence_pull_ball::make(p, Qt::black); }},
        {"看板以批量方式传达",  [] (QPointF p)->up_item { return board_arrival::make(p, Qt::black); }},
        {"均衡生产",  [] (QPointF p)->up_item { return balanced_production::make(p, Qt::black); }},
        {"现场调度",  [] (QPointF p)->up_item { return adjustment_on_scene::make(p, Qt::black); }},
        {"改善",  [] (QPointF p)->up_item { return improvement::make(p, Qt::red); }},
        {"缓冲或安全库存",  [] (QPointF p)->up_item { return cache_or_safe_storage::make(p, Qt::black); }},
        {"操作员", [] (QPointF p)->up_item { return operating_personnel::make (p, Qt::black); }},
        {"看板站", [] (QPointF p)->up_item { return board_station::make (p, Qt::black); }},
        {"生产控制部门", [] (QPointF p)->up_item { return production_control_department::make (p, Qt::black); }},
        //{"增值比", [] (QPointF p)->up_item { return value_added_radtio::make(p,Qt::black);}},
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
        return traditional_info_flow::make(start, end, Qt::blue);
    }
    else if (name == "电子信息流")
    {
        return electric_info_flow::make(start, end, Qt::blue);
    }
    else if (name == "物流")
    {
        return material_flow::make(start, end, Qt::black);
    }
    else if (name == "先进先出")
    {
        return fifo::make (start, end, Qt::black);
    }
    else if (name == "成品发送至顾客")
    {
        auto ret = product_to_customer::make(start, end, Qt::black);
        if (! ret)
        {
            qDebug () << "product_to_customer is nullptr";
        }
        return ret;
    }
    qDebug () << __PRETTY_FUNCTION__ << " kengdie le ";

    return nullptr;
}


%>
