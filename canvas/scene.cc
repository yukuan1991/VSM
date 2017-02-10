#include "canvas/scene.h"
#include <QGraphicsItem>
#include "utility/raii.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>

namespace canvas
<%

void scene::init()
{
    connect (this, &scene::selectionChanged, [this] { report_selection (); });
    setSceneRect ({0, 0, 1920, 1080});
}

const nlohmann::json scene::selected_item_attribute()
{
    auto selected = selectedItems();
    if (selected.size() != 1)
    {
        return {};
    }

    auto item_selected = dynamic_cast<item::item*> (selected [0]);

    if (item_selected == nullptr)
    {
        return {};
    }

    return item_selected->data();
}

void scene::set_item_attribute(string_view key, std::__cxx11::string value)
{
    auto selected = selectedItems();
    if (selected.size () != 1)
    {
        return;
    }
    auto item_selected = dynamic_cast<item::item*> (selected [0]);
    if (item_selected == nullptr)
    {
        return;
    }
    item_selected->set_attribute (key, value);
    item_selected->update ();
}

scene::~scene()
{

}


void scene::report_selection()
{
    if (selectedItems ().size () == 1)
    {
        emit selection_changed(true);
    }
    else
    {
        emit selection_changed(false);
    }
}

%>
