#ifndef CANVAS_SCENE_H
#define CANVAS_SCENE_H

#include <QGraphicsScene>
#include <utility>

class canvas_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    template<typename ... ARGS>
    canvas_scene(ARGS&& ... args)
        :QGraphicsScene (std::forward<ARGS> (args)...)
    {
        init ();
    }
    void init ();
private:
    void on_selection_changed ();
};

#endif // CANVAS_SCENE_H
