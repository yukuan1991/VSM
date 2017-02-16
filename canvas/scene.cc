#include "canvas/scene.h"
#include <QGraphicsItem>
#include "utility/raii.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "item/production_sequence.h"
#include "utility/algorithm.hpp"
#include "utility/containers.hpp"
#include <assert.h>

namespace canvas
<%

using namespace std;

const QColor scene::background_color (230, 230, 230);


void scene::init()
{
    connect (this, &scene::selectionChanged, [this] { report_selection (); });
    setSceneRect ({0, 0, 1500, 1200});
    setBackgroundBrush(background_color);
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
    auto center_point = sceneRect ().center();
    effective_rect_ = QRectF (center_point - QPointF (width / 2, height / 2), QSizeF (width, height));

    painter->drawRect(effective_rect_);

    vector<pair<qreal, qreal>> sequences;
    for (auto it : items ())
    {
        auto sequence = dynamic_cast<item::item*>(it);
        if (sequence == nullptr)
        {
            continue;
        }
        if (sequence->item_type() != "生产工序")
        {
            continue;
        }

        auto begin_x = it->mapToScene (it->boundingRect().topLeft()).x();
        auto end_x = it->mapToScene(it->boundingRect().topRight()).x();
        if (effective_rect_.left() > end_x or effective_rect_.right () < begin_x)
        {
            continue;
        }
        auto begin_y = it->mapToScene (it->boundingRect().topLeft ()).y();
        auto end_y = it->mapToScene(it->boundingRect().bottomRight ()).y();
        if (effective_rect_.top() > begin_y or effective_rect_.bottom() < end_y)
        {
            continue;
        }

        sequences.emplace_back (std::max (effective_rect_.left(), begin_x),
                                std::min (effective_rect_.right (), end_x));
    }
    std::sort (begin (sequences), end (sequences));

    for (unsigned i = 0; i < sequences.size (); i++)
    {
        auto j = i + 1;
        while (j < sequences.size ())
        {
            auto first1 = sequences [i].first;
            auto first2 = sequences [j].first;
            auto second1 = sequences [i].second;
            auto second2 = sequences [j].second;

            if ((first1 > first2 and first1 < second2)  or
                    (second1 > first2 and second1 < second2) or
                    (first2 > first1 and first2 < second1) or
                    (second2 > first1 and second2 < second1))
            {
                auto final_first = std::min (first1, first2);
                auto final_second = std::max (second1, second2);
                sequences [i] = {final_first, final_second};
                sequences.erase(begin (sequences) + j);
            }
            else
            {
                j++;
            }
        }
    }

    qreal last = effective_rect_.left();
    painter->setPen ({Qt::black, 2.0});
    auto low_ground = effective_rect_.bottom () - 20;
    auto high_ground = low_ground - 30;
    for (auto & it : sequences)
    {
        QLineF flat_line (QPointF (last, high_ground), QPointF (it.first, high_ground));
        painter->drawLine(flat_line);
        QLineF vertical_line (QPointF (it.first, high_ground), QPointF (it.first, low_ground));
        painter->drawLine(vertical_line);
        painter->drawLine(QPointF (it.first, low_ground), QPointF (it.second, low_ground));
        painter->drawLine(QPointF (it.second, high_ground), QPointF (it.second, low_ground));
        last = it.second;
    }
    painter->drawLine(QPointF (last, high_ground), QPointF (effective_rect_.right (), high_ground));
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
