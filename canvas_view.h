#pragma once

#include <QGraphicsView>
#include <QGraphicsItem>

class canvas_view : public QGraphicsView
{
    Q_OBJECT
signals:
    void scale_changed (double);
public:
    constexpr static auto path_role = Qt::UserRole + 100;
    constexpr static auto remark_role = Qt::UserRole + 101;
public:
    canvas_view(QWidget* parent = nullptr);
    canvas_view(QGraphicsScene* scene, QWidget* parent = nullptr);
    void init ();
    void scale_object (double factor);

protected:
    void keyPressEvent (QKeyEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
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
};


template<typename CALLABLE>
void canvas_view::hold_position (QGraphicsItem* item, CALLABLE&& c)
{
    auto old_center = item->mapRectToScene (item->boundingRect ()).center ();
    c (item);
    auto new_center = item->mapRectToScene (item->boundingRect ()).center ();
    auto diff = new_center - old_center;

    item->moveBy (- diff.x (), - diff.y ());
}
