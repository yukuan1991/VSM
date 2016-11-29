#include "canvas_scene.h"
#include <QGraphicsItem>


void canvas_scene::init()
{
    connect (this, &canvas_scene::selectionChanged, [this] { on_selection_changed (); });
    setSceneRect ({0, 0, 10000, 10000});
}

void canvas_scene::on_selection_changed()
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
