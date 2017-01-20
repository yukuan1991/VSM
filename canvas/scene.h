#pragma once

#include <QGraphicsScene>
#include <utility>
#include "json.hpp"
#include <experimental/optional>
#include <memory>
#include "item/material_flow.h"

namespace item
{
class material_flow;
}

namespace canvas
<%

using std::experimental::nullopt;

class scene : public QGraphicsScene
{
    Q_OBJECT
public:
    template<typename ... ARGS>
    scene(ARGS&& ... args) : QGraphicsScene (std::forward<ARGS> (args)...) { init (); }
    void init ();
    bool load (const nlohmann::json & data);
    ~scene () override;
protected:
private:
    void on_selection_changed ();

private:
};

%>
