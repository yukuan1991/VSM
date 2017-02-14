#pragma once


#include <QObject>
#include <QGraphicsItem>
#include "utility/raii.hpp"
#include "json.hpp"
#include <experimental/string_view>
#include <experimental/optional>
#include "utility/containers.hpp"

namespace item
<%
using std::experimental::string_view;
using std::experimental::optional;
using std::experimental::nullopt;

enum class selected_item : bool
{
    yes = true,
    no = false
};

class item : public QGraphicsObject
{
    Q_OBJECT
signals:
    void name_changed (const QString&);
    void color_changed (const QColor&);
public:
    qreal width () { return item_width_; }
    qreal height () { return item_height_; }
    void set_name (string name) { item_info_ ["name"] = name; }
    string name ();
    const QString& item_type () { return type_; }
    const QColor& color () { return color_; }
    void set_color (QColor c) { color_ = ::move (c); emit color_changed (c); }
    void set_attribute (string_view key, std::string value = {});
    void apply_z_value (selected_item yes_or_no);
    nlohmann::json attributes () { return item_info_ ["attribute"]; }
    virtual QRectF shape_rect () const { return boundingRect(); }

    QRectF boundingRect () const override;
protected:
    explicit item(QGraphicsItem *parent = 0);
    static void set_dash (QPainter* painter);
    void set_z_value (qreal value) { z_value_ = value; setZValue(value); }
    qreal z_value () { return z_value_; }

    string find_json_value (const string& key, const nlohmann::json& data);


    /// overrides
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
    void paint (QPainter * painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void paint_attribute (QPainter* painter);
protected:
    qreal item_width_ = 100;
    qreal item_height_ = 0.8 * item_width_;
    QString type_;
    nlohmann::json item_info_;
    static constexpr qreal small_object_ratio = 2;
    static constexpr qreal small_object_height = 4;
    bool show_frame_ = false;
private:
    QColor color_ = Qt::black;
    qreal z_value_ = 0;
};

%>

