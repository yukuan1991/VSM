#include "canvas/scene.h"
#include <QGraphicsItem>
#include "utility/raii.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

namespace canvas
<%

void scene::init()
{
    connect (this, &scene::selectionChanged, [this] { on_selection_changed (); });
    setSceneRect ({0, 0, 500, 500});
}

const nlohmann::json scene::selected_item_attribute()
{
    if (selected_item_)
    {
        return selected_item_->data();
    }
    else
    {
        return {};
    }
}

scene::~scene()
{

}

void scene::on_selection_changed()
{
    auto selected = selectedItems ();
    auto children = items ();

    if (selected.size () == 1)
    {
        emit selection_changed(true);
        selected_item_ = dynamic_cast<item::item*> (selected [0]); assert (selected_item_);
    }
    else
    {
        emit selection_changed(false);
        selected_item_ = nullptr;
    }

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

%>
