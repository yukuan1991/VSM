﻿#include "canvas/scene.h"
#include <QGraphicsItem>
#include "utility/raii.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

namespace canvas
<%

void scene::init()
{
    connect (this, &scene::selectionChanged, [this] { adjust_z_value (); });
    connect (this, &scene::selectionChanged, [this] { report_selection (); });

    setSceneRect ({0, 0, 500, 500});
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

void scene::adjust_z_value()
{
    auto selected = selectedItems ();
    auto children = items ();


    for (auto & it : children)
    {
        if (std::find (selected.begin (), selected.end (), it) != selected.end ())
        {
            it->setZValue (1);
        }
        else
        {
            it->setZValue (0);
        }
    }
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
