#include "canvas/scene.h"
#include <QGraphicsItem>
#include "utility/raii.hpp"
#include <QGraphicsSceneMouseEvent>

namespace canvas
<%

void scene::init()
{
    connect (this, &scene::selectionChanged, [this] { adjust_z_value (); });
    setSceneRect ({0, 0, 500, 500});
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

%>
