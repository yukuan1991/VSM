#pragma once


#include <QGraphicsObject>
#include "utility/raii.hpp"
#include "json.hpp"
#include "utility/interface.hpp"
#include "utility/containers.hpp"



namespace item
<%
using std::experimental::string_view;
using std::experimental::optional;
using std::experimental::nullopt;
using nlohmann::json;
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
    static unique_ptr<item> make (nlohmann::json data, item* parent = nullptr);
    static json dump_scene (not_null<QGraphicsScene*> scene);

    void set_name (const string & name) { item_info_ ["name"] = name; }
    static const json & json_find (const json& data, const string & key);
    string name ();
    string item_type () const noexcept;
    void set_item_type (const string & type);
    void set_attribute (string_view key, std::string value = {});
    std::string attribute (const string& key);
    void apply_z_value (selected_item yes_or_no);
    const json& attributes () { return item_info_ ["attribute"]; }
    const json & dump () { return item_info_; }

protected:
    explicit item (json data, QPointF pos, item* parent);
    explicit item(QGraphicsItem *parent = 0);
    void set_z_value (qreal value) { z_value_ = value; setZValue(value); }
    qreal z_value () const { return z_value_; }

    static string find_json_value (const string& key, const nlohmann::json& data);
    bool show_frame () const { return show_frame_; }
    const QColor & selected_color () { return selected_color_; }

    /// overrides
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
private:
    bool show_frame_ = false;
    nlohmann::json item_info_;
    qreal z_value_ = 0;
    const QColor selected_color_ = Qt::red;
};

%>

