#pragma once

#include <QGraphicsScene>
#include <utility>
#include "json.hpp"
#include <experimental/optional>
#include <memory>
#include "item/material_flow.h"
#include <experimental/string_view>

namespace item
{
class material_flow;
}

namespace canvas
<%

using std::experimental::nullopt;
using std::experimental::string_view;

class scene : public QGraphicsScene
{
    Q_OBJECT
public:
    template<typename ... ARGS>
    scene(ARGS&& ... args) : QGraphicsScene (std::forward<ARGS> (args)...) { init (); }
    void init ();
    bool load (const nlohmann::json & data);
    nlohmann::json selected_item_attribute ();
    void set_item_attribute (string_view key, std::string value = {});
    ~scene () override;

signals:
    void selection_changed (bool);
protected:
private:
    void adjust_z_value ();
    void report_selection ();

private:
    item::item* selected_item_ = nullptr;
};

%>
