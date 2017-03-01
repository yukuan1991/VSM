﻿#include "arrow_item.h"

namespace item {

unique_ptr<arrow_item> arrow_item::make(json data, item *parent)
{
    return nullptr;
}

arrow_item::arrow_item (nlohmann::json data, QPointF pos, item *parent)
    :item (::move (data), pos, parent)
{

}

bool arrow_item::init() try
{
    std::tie (p1_, p2_) = get_pos (dump ());

    return true;
}
catch (const std::exception & e)
{
    return false;
}


tuple<QPointF, QPointF> arrow_item::get_pos(const json &data)
{
    auto && json_p1 = json_find (data, "p1");
    auto && json_p2 = json_find (data, "p2");
    const qreal x1 = json_find (json_p1, "x");
    const qreal y1 = json_find (json_p1, "y");

    const qreal x2 = json_find(json_p2, "x");
    const qreal y2 = json_find(json_p2, "y");

    const QPointF p1 (x1, y1), p2 (x2, y2);

    return std::make_tuple (p1, p2);
}

} // namespace item
