#include "arrow_item.h"
#include "item/material_flow.h"

namespace item {

arrow_item::arrow_item (nlohmann::json data, QPointF pos, abstract_item *parent)
    :abstract_item (::move (data), pos, parent)
{

}

bool arrow_item::init() try
{
    std::tie (p1_, p2_) = get_pos (dump ());
    auto line = QLineF (p1_, p2_);
    angle_ = line.angle ();
    radius_ = line.length () / 2;
    start_pos_ = QPointF (- radius_, 0);
    stop_pos_ = QPointF (radius_, 0);
    return true;
}
catch (const std::exception &)
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
