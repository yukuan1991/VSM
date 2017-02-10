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
    setSceneRect ({0, 0, 1500, 1500});
    setBackgroundBrush(QColor (230, 230, 230));
    connect (this, &scene::changed, this, &scene::on_scene_changed);
}

nlohmann::json scene::selected_item_attribute()
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

    return item_selected->attributes();
}

void scene::set_item_attribute(string_view key, string value)
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

void scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);

    painter->setBrush(Qt::white);
    constexpr qreal width = 1000;
    constexpr qreal height = 1000 * 1.4142135;
    auto center_point = sceneRect ().center();

    painter->drawRect(QRectF (center_point - QPointF (width / 2, height / 2), QSizeF (width, height)));
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

void scene::on_scene_changed(const QList<QRectF> &areas)
{
    for (auto & it : areas)
        qDebug () << it;
}

%>
