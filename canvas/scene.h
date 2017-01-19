#pragma once

#include <QGraphicsScene>
#include <utility>
#include "json.hpp"

namespace canvas
<%

class scene : public QGraphicsScene
{
    Q_OBJECT
public:
    template<typename ... ARGS>
    scene(ARGS&& ... args) : QGraphicsScene (std::forward<ARGS> (args)...) { init (); }
    void init ();
    bool load (const nlohmann::json & data);
private:
    void on_selection_changed ();
};

%>
