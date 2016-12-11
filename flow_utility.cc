#include "flow_utility.h"
#include <QFile>
#include <QFileInfo>

namespace flow_utility_detail
<%

static constexpr auto path_role = Qt::UserRole + 100;

%>
using namespace flow_utility_detail;

QGraphicsSvgItem* add_svg_to_scene(const QString &path, not_null<QGraphicsScene *> scene, QPointF pos)
{
    if (QFile (path).exists ())
    {
        return nullptr;
    }

    auto item = std::make_unique<QGraphicsSvgItem> (path);
    auto raw_item = item.get ();
    item->setPos(pos);
    item->setData(path_role, QFileInfo (path).baseName());
    item->setFlags (QGraphicsSvgItem::ItemIsSelectable | QGraphicsSvgItem::ItemIsMovable);
    item->setZValue (0);

    scene->addItem(item.release());

    return raw_item;
}
