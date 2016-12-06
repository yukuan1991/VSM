#include "canvas_body.h"
#include "json.hpp"
#include "utility/raii.hpp"

canvas_body::canvas_body(QWidget *parent)
    :canvas_view (parent)
{
    setScene (&scene_);
}

void canvas_body::file_new_tile()
{

}

std::string canvas_body::dump()
{
    nlohmann::json data;
    nlohmann::json items = nlohmann::json::array();
    for (auto & it : this->items())
    {
        nlohmann::json item_data;
        item_data ["scale"] = it->matrix().m11();
        item_data ["pos"]["x"] = it->pos().x ();
        item_data ["pos"]["y"] = it->pos().y ();
        item_data ["z-value"] = it->zValue();
        items.push_back(::move (item_data));
    }
    data ["items"] = ::move (items);
    data ["view-scale"] = matrix().m11 ();

    return data.dump(4);
}
