#include "canvas_view.h"
#include <QWheelEvent>
#include <QMatrix>
#include <QDebug>
#include <QFileInfo>
#include <QKeyEvent>
#include "utility/raii.hpp"
#include <QTransform>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include "flow_utility.h"
#include "defs.hpp"
#include <QGraphicsSvgItem>
#include <assert.h>
#include <QGLWidget>



canvas_view::canvas_view(QWidget *parent)
        :QGraphicsView (parent)
{
    init ();
}

canvas_view::canvas_view(QGraphicsScene *scene, QWidget *parent)
        :QGraphicsView (scene, parent)
{
    init ();
}

void canvas_view::init()
{
    setDragMode (RubberBandDrag);
    setRubberBandSelectionMode (Qt::IntersectsItemShape);
    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
}

void canvas_view::wheelEvent(QWheelEvent *event)
{
    SCOPE_EXIT { QGraphicsView::wheelEvent(event); };

    if (! (event->modifiers() & Qt::ControlModifier))
    {
        return;
    }

    if (event->delta() > 0)
    {
        scale_object (1.1);
    }
    else
    {
        scale_object (1 / 1.1);
    }

    event->accept ();
}

void canvas_view::keyPressEvent(QKeyEvent *event)
{
    SCOPE_EXIT { QGraphicsView::keyPressEvent (event); };

    if (event->modifiers () & Qt::CTRL and event->key () == Qt::Key_A)
    {
        select_all ();
        event->accept ();
    }

    if (event->modifiers () & Qt::CTRL and event->key () == Qt::Key_R)
    {
        rotate_selected ();
        event->accept ();
    }

    if (event->key () == Qt::Key_Delete)
    {
        delete_selected ();
        event->accept ();
    }
}

void canvas_view::mouseDoubleClickEvent(QMouseEvent *event)
{
    SCOPE_EXIT { QGraphicsView::mouseDoubleClickEvent (event); };

    auto item = itemAt (event->pos ());
    if (item == nullptr)
    {
        return;
    }

    hold_position (item, [] (auto&& item) { item->resetMatrix (); });
}

void canvas_view::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData ()->hasFormat ("svg") and event->source () != this)
    {
        event->accept ();
    }
    else
    {
        QGraphicsView::dragEnterEvent (event);
    }
}

void canvas_view::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData ()->hasFormat ("svg") and event->source () != this)
    {
        event->accept ();
    }
    else
    {
        QGraphicsView::dragMoveEvent (event);
    }
}

void canvas_view::dropEvent(QDropEvent *event)
{
    if (event->mimeData ()->hasFormat ("svg") and event->source () != this)
    {
        svg_drop_action (event);
        event->accept ();
    }
    else
    {
        QGraphicsView::dropEvent (event);
    }
}

void canvas_view::select_all()
{
    auto list = items ();
    for (auto & item : list)
    {
        item->setSelected (true);
    }
}

void canvas_view::rotate_selected()
{
    auto selected = scene ()->selectedItems ();
    for (auto & item : selected)
    {
        hold_position (item, [] (auto&& item) { item->setMatrix (item->matrix ().rotate (rotate_arg)); });
    }
}

void canvas_view::scale_object(double factor)
{
    auto set_scale = [factor, this] (auto&& obj)
    {
        auto m = obj->matrix ();

        auto scale_factor = m.m11 ();
        scale_factor *= factor;

        auto m_after = QMatrix ();
        m_after.scale (scale_factor, scale_factor);
        obj->setMatrix (m_after);

        if (reinterpret_cast<void*> (obj) == reinterpret_cast<void*> (this))
        {
            emit scale_changed (scale_factor);
        }
    };

    auto selected = scene ()->selectedItems ();
    if (selected.isEmpty ())
    {
        set_scale (this);
    }
    else
    {
        for (auto & item : selected)
        {
            hold_position (item, set_scale);
        }
    }
}

void canvas_view::svg_drop_action(QDropEvent *event)
{
    QString path = event->mimeData ()->data ("svg");


    auto mouse_pos = mapToScene(event->pos());
    auto item = add_svg_to_scene(path, scene (), mouse_pos); assert (item);
    auto new_center = item->mapRectToScene (item->boundingRect ()).center ();

    auto diff = new_center - mouse_pos;
    item->moveBy (- diff.x (), - diff.y ());
}

void canvas_view::delete_selected()
{
    for (auto & it : scene ()->selectedItems ())
    {
        delete it;
    }
}
