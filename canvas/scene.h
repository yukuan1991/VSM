#pragma once

#include <QGraphicsScene>
#include <QColor>
#include <utility>
#include "json.hpp"
#include <memory>
#include "item/material_flow.h"
#include "utility/containers.hpp"
#include "item/production_sequence.h"


namespace item
{
class material_flow;
}

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
    nlohmann::json selected_item_attribute ();
    void set_item_attribute (string_view key, std::string value = {});
    QRectF effective_rect () { return effective_rect_; }
    ~scene () override;

signals:
    void selection_changed (bool);
protected:
    void drawBackground (QPainter* painter, const QRectF& rect) override;
private:
    void adjust_z_value ();
    void report_selection ();
    void product_sequence_deletion ();
private:
    item::item* selected_item_ = nullptr;
    qreal height = 1000;
    qreal width = 1000 * 1.4142135;

    const static QColor background_color;
    QRectF effective_rect_;
};

%>
