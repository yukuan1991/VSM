#include "canvas/view.h"
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
#include "item/traditional_info_flow.h"
#include "item/electric_info_flow.h"
#include "item/maker.hpp"



namespace canvas
<%

view::view(QWidget *parent)
    :QGraphicsView (parent)
{
    init ();
}

view::view(QGraphicsScene *scene, QWidget *parent)
    :QGraphicsView (scene, parent)
{
    init ();
}

void view::init()
{
    setDragMode (RubberBandDrag);
    setRubberBandSelectionMode (Qt::IntersectsItemShape);
    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
}

void view::wheelEvent(QWheelEvent *event)
{
    SCOPE_EXIT { QGraphicsView::wheelEvent(event); };

    if (!(event->modifiers() & Qt::ControlModifier))
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

void view::keyPressEvent(QKeyEvent *event)
{
    SCOPE_EXIT { QGraphicsView::keyPressEvent (event); };

    if (event->modifiers () & Qt::CTRL and event->key () == Qt::Key_A)
    {
        select_all ();
        event->accept ();
    }

    if (event->key () == Qt::Key_Delete)
    {
        delete_selected ();
        event->accept ();
    }
}

void view::mousePressEvent(QMouseEvent *event)
{
    if (arrow_state_.isEmpty())
    {
        QGraphicsView::mousePressEvent(event);
    }
    else if (arrow_state_ == "看板用信息流")
    {
        ///
    }
    else
    {
        last_pressed_ = mapToScene(event->pos());
        tmp_arrow_.emplace (nullptr);
    }
}

void view::mouseMoveEvent(QMouseEvent *event)
{
    if (tmp_arrow_)
    {
        auto end_ptr = mapToScene(event->pos ());

        if (arrow_state_ == "传统信息流")
            tmp_arrow_.emplace (item::traditional_info_flow::make(last_pressed_, end_ptr));
        else if (arrow_state_ == "电子信息流")
            tmp_arrow_.emplace (item::electric_info_flow::make(last_pressed_, end_ptr));

        if (tmp_arrow_.value() != nullptr)
            scene()->addItem(tmp_arrow_->get());
    }
    else
        QGraphicsView::mouseMoveEvent(event);
}


void view::mouseReleaseEvent(QMouseEvent *event)
{
    if (tmp_arrow_)
    {
        tmp_arrow_.value().release();
        tmp_arrow_ = nullopt;
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void view::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData ()->hasFormat ("item") and event->source () != this)
    {
        event->accept ();
    }
    else
    {
        QGraphicsView::dragEnterEvent (event);
    }
}

void view::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData ()->hasFormat ("item") and event->source () != this)
    {
        //qDebug () << event->mimeData()->data("item").toStdString().data();
        event->accept ();
    }
    else
    {
        QGraphicsView::dragMoveEvent (event);
    }
}

void view::dropEvent(QDropEvent *event)
{
    if (event->mimeData ()->hasFormat ("item") and event->source () != this)
    {
        item_drop_action (event);
        event->accept ();
    }
    else
    {
        QGraphicsView::dropEvent (event);
    }
}

void view::select_all()
{
    auto list = items ();
    for (auto & item : list)
    {
        item->setSelected (true);
    }
}

void view::scale_object(double factor)
{
    auto set_scale = [factor, this] (auto&& obj)
    {
        auto m = obj->matrix ();

        auto scale_factor = m.m11 ();
        scale_factor *= factor;

        if (scale_factor < 1)
        {
            scale_factor = 1;
        }

        auto m_after = QMatrix ();
        m_after.scale (scale_factor, scale_factor);
        obj->setMatrix (m_after);

        if (reinterpret_cast<void*> (obj) == reinterpret_cast<void*> (this))
        {
            emit scale_changed (scale_factor);
            }
    };

    set_scale (this);
}

void view::item_drop_action(QDropEvent *event)
{
    QString type = event->mimeData ()->data ("item");

    auto scene_pos = mapToScene(event->pos());
    auto the_item = item::make_item (type, scene_pos);

    if (the_item == nullptr)
    {
        return;
    }
    scene ()->addItem(the_item.get ());

    auto new_center = the_item->mapRectToScene (the_item->boundingRect ()).center ();

    auto diff = new_center - scene_pos;
    the_item->moveBy (- diff.x (), - diff.y ());

    the_item.release();
}

void view::delete_selected()
{
    for (auto & it : scene ()->selectedItems ())
    {
        delete it;
    }
}

%>
