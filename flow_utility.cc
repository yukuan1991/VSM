#include "flow_utility.h"
#include <QFile>

QGraphicsSvgItem* add_svg_to_scene(const QString &path, not_null<QGraphicsScene *> scene, QPointF pos)
{
    if (QFile (path).exists ())
    {
        return nullptr;
    }

    auto item = std::make_unique<QGraphicsSvgItem> (path);
    auto raw_item = item.get ();


    return raw_item;
}
