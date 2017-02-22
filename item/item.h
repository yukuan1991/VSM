﻿#pragma once


#include <QObject>
#include <QGraphicsItem>
#include "utility/raii.hpp"
#include "json.hpp"
#include <experimental/string_view>
#include <experimental/optional>
#include "utility/interface.hpp"
#include "utility/containers.hpp"

namespace item
<%
using std::experimental::string_view;
using std::experimental::optional;
using std::experimental::nullopt;
using namespace std;

enum class selected_item : bool
{
    yes = true,
    no = false
};

class item : public QGraphicsObject
{
    Q_OBJECT
public:
    friend nlohmann::json dump_scene (not_null<QGraphicsScene*> scene);

    void set_name (const string & name) { item_info_ ["name"] = name; }
    string name ();

    string item_type () const noexcept;

    void set_item_type (const string & type);

    void set_attribute (string_view key, std::string value = {});
    std::string attribute (const string& key);
    void apply_z_value (selected_item yes_or_no);
    nlohmann::json attributes () { return item_info_ ["attribute"]; }

    QRectF boundingRect () const override;
protected:
    explicit item(QGraphicsItem *parent = 0);
    void set_z_value (qreal value) { z_value_ = value; setZValue(value); }
    qreal z_value () { return z_value_; }

    string find_json_value (const string& key, const nlohmann::json& data);
    bool show_frame () const { return show_frame_; }

    /// overrides
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
protected:
    qreal item_width_ = 100;
    qreal item_height_ = 0.8 * item_width_;
    nlohmann::json item_info_;
    static constexpr qreal small_object_ratio = 2;
    static constexpr qreal small_object_height = 4;
    bool show_frame_ = false;
private:
    void load_item_info (nlohmann::json item_info) { item_info_ = ::move (item_info); }
    nlohmann::json save_item_info () { return item_info_; }
private:
    qreal z_value_ = 0;
};

%>

