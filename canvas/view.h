#pragma once

#include <QGraphicsView>
#include <QGraphicsItem>
#include <experimental/optional>
#include "utility/memory.hpp"
#include "utility/raii.hpp"
#include "utility/containers.hpp"


namespace item
{
class item;
}

namespace canvas
<%

class view : public QGraphicsView
{
    Q_OBJECT
signals:
    void scale_changed (double);
    void set_arrow_state (const QString&);
public:
    explicit view(QWidget* parent = nullptr);
    explicit view(QGraphicsScene* scene, QWidget* parent = nullptr);
    void init ();

    /// 如果比例小于1则用1
    void scale_object (double factor);

    //void set_arrow_state (QString state) { arrow_state_ = ::move (state); }
    void on_state_changed (const QString& state);
    ~view () override;

protected:
    void keyPressEvent (QKeyEvent* event) override;

    void mousePressEvent (QMouseEvent* event) override;
    void mouseMoveEvent (QMouseEvent* event) override;
    void mouseReleaseEvent (QMouseEvent* event) override;

    void board_info_press_event (QMouseEvent* event);
    void board_info_move_event (QMouseEvent* event);
    void board_info_release_event (QMouseEvent* event);

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent (QDropEvent* event) override;
    void wheelEvent (QWheelEvent* event) override;
private:
    void select_all ();
    void item_drop_action (QDropEvent* event);
    void delete_selected ();
    void finish_board_info (vector<unique_ptr<QGraphicsLineItem>> lines);
    static unique_ptr<QGraphicsLineItem> make_line (QPointF p1, QPointF p2);

    template<typename CALLABLE>
    static void hold_position (QGraphicsItem* item, CALLABLE&& c);
private:
    optional<unique_ptr<item::item>> tmp_arrow_;
    QString arrow_state_;
    QPointF last_pressed_;
    vector<unique_ptr<QGraphicsLineItem>> board_tmp_item_;
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
