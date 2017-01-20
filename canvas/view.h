#pragma once

#include <QGraphicsView>
#include <QGraphicsItem>
#include <experimental/optional>
#include <memory>
#include "item/material_flow.h"



namespace item
{
class material_flow;
}

namespace canvas
<%
using std::experimental::optional;
using std::experimental::nullopt;

class view : public QGraphicsView
{
    Q_OBJECT
signals:
    void scale_changed (double);
public:
    constexpr static auto path_role = Qt::UserRole + 100;
    constexpr static auto remark_role = Qt::UserRole + 101;
public:
    explicit view(QWidget* parent = nullptr);
    explicit view(QGraphicsScene* scene, QWidget* parent = nullptr);
    void init ();
    void scale_object (double factor);
    void set_arrow_state (QString state) { arrow_state_ = ::move (state); }

protected:
    void keyPressEvent (QKeyEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent (QMouseEvent* event) override;
    void mouseMoveEvent (QMouseEvent* event) override;
    void mouseReleaseEvent (QMouseEvent* event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent (QDropEvent* event) override;
    void wheelEvent (QWheelEvent* event) override;
private:
    void select_all ();
    void rotate_selected ();
    void svg_drop_action (QDropEvent* event);
    void delete_selected ();

    template<typename CALLABLE>
    static void hold_position (QGraphicsItem* item, CALLABLE&& c);
private:
    constexpr static double rotate_arg = 90;

    optional<std::unique_ptr<item::item>> tmp_arrow_ = std::experimental::nullopt;
    QString arrow_state_;
    QPointF last_pressed_;
};


template<typename CALLABLE>
void view::hold_position (QGraphicsItem* item, CALLABLE&& c)
{
    auto old_center = item->mapRectToScene (item->boundingRect ()).center ();
    c (item);
    auto new_center = item->mapRectToScene (item->boundingRect ()).center ();
    auto diff = new_center - old_center;

    item->moveBy (- diff.x (), - diff.y ());
}

%>
