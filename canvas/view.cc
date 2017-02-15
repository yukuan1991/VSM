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
#include "defs.hpp"
#include <QGraphicsSvgItem>
#include <assert.h>
#include <QGLWidget>
#include "qt-tools/graphics.hpp"
#include "item/board_info_flow.h"
#include <QPainter>
#include <QMenu>
#include "item/maker.hpp"
#include "item/text_item.h"


namespace canvas
<%

view::view(QWidget *parent)
    :QGraphicsView (parent)
    , tmp_arrow_ (nullptr)
{
    init ();
}

view::view(QGraphicsScene *scene, QWidget *parent)
    :QGraphicsView (scene, parent)
    ,tmp_arrow_ (nullptr)
{
    init ();
}

void view::init()
{
    setRenderHint (QPainter::Antialiasing, true);
    //setDragMode (RubberBandDrag);
    //setRubberBandSelectionMode (Qt::IntersectsItemShape);
    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    connect (this, &view::set_arrow_state, this, &view::on_state_changed);
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
        board_info_press_event(event);
    }
    else if (arrow_state_ == "文字")
    {
        return;
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

        tmp_arrow_ = item::make_arrow(arrow_state_, last_pressed_, end_ptr);

        if (tmp_arrow_.value() != nullptr)
        {
            scene()->addItem(tmp_arrow_->get());
        }
    }
    else if (arrow_state_ == "看板用信息流")
    {
        board_info_move_event(event);
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }
}


void view::mouseReleaseEvent(QMouseEvent *event)
{
    if (tmp_arrow_)
    {
        if (*tmp_arrow_)
        {
            emit arrow_finished ();
            tmp_arrow_.value().release();
        }
        tmp_arrow_ = nullopt;
    }
    else if (arrow_state_ == "看板用信息流")
    {
        board_info_release_event(event);
    }
    else if (arrow_state_ == "文字")
    {
        add_text (event);
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void view::board_info_press_event(QMouseEvent *event)
{
    auto scene_pos = mapToScene(event->pos());

    if (event->button() == Qt::LeftButton)
    {
        if (board_tmp_item_.empty())
        {
            board_tmp_item_.emplace_back (make_line (scene_pos, scene_pos));
            scene ()->addItem (board_tmp_item_.back ().get ());
            return;
        }

        auto& last_item = board_tmp_item_.back ();
        auto last_ptr = last_item->line ().p1 ();
        if (distance (scene_pos, last_ptr) < 10)
        {
            return;
        }

        last_item->setLine({last_ptr, scene_pos});
        board_tmp_item_.emplace_back (make_line (scene_pos, scene_pos));
        scene ()->addItem (board_tmp_item_.back ().get ());
    }
    else if (event->button() == Qt::RightButton)
    {
        if (board_tmp_item_.empty())
        {
            return;
        }

        finish_board_info (::move (board_tmp_item_));
    }
}


void view::board_info_move_event(QMouseEvent *event)
{
    if (board_tmp_item_.empty())
    {
        return;
    }

    auto& last_item = board_tmp_item_.back();
    auto p1 = last_item->line().p1();
    last_item->setLine({p1, mapToScene (event->pos())});
}

void view::board_info_release_event(QMouseEvent *event)
{
    Q_UNUSED (event);
}

void view::add_text(QMouseEvent *event)
{
    auto scene_pos = mapToScene (event->pos ());
    auto text = text_item::make (scene_pos);
    auto center = text->mapToScene(text->boundingRect ().center ());
    auto diff = center - scene_pos;
    text->setPos(scene_pos - diff);
    text->setTextInteractionFlags(Qt::TextEditorInteraction);
    scene ()->addItem(text.release ());
    emit arrow_finished ();

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

void view::on_state_changed(const QString &state)
{
    board_tmp_item_.clear();

    SCOPE_EXIT { arrow_state_ = state; };
    if (state == "看板用信息流")
    {
        setMouseTracking(true);
    }
    else
    {
        setMouseTracking(false);
    }
}

view::~view()
{

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

void view::finish_board_info(vector<unique_ptr<QGraphicsLineItem>> lines)
{
    QMenu menu;
    auto confirm = menu.addAction ("确定");
    menu.addAction ("取消");
    connect (confirm, &QAction::triggered, [&]
    {
        scene ()->addItem (item::board_info_flow::make (::move (lines), Qt::black).release ());
        emit arrow_finished ();
    });
    menu.exec(QCursor::pos());
}

unique_ptr<QGraphicsLineItem> view::make_line(QPointF p1, QPointF p2)
{
    auto ret = std::make_unique<QGraphicsLineItem> (QLineF (p1, p2));
    QPen pen;
    pen.setWidthF (2.0);
    pen.setStyle (Qt::DashLine);
    ret->setPen (pen);
    return ret;
}

%>
