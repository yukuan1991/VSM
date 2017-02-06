#pragma once


#include <QObject>
#include <QGraphicsItem>
#include "utility/raii.hpp"
#include "json.hpp"
#include <experimental/string_view>
#include <experimental/optional>

namespace item
<%
using std::experimental::string_view;
using std::experimental::optional;
using std::experimental::nullopt;

class item : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    qreal width () { return item_width; }
    qreal height () { return item_height; }
    const QString& name () { return name_; }
    void set_name (QString s) { name_ = ::move (s);  emit name_changed (name_); }
    const QString& type () { return type_; }
    const QColor& color () { return color_; }
    void set_color (QColor c) { color_ = ::move (c); emit color_changed (c); }
    void set_data (const nlohmann::json& data)  { item_info_ = data; }
    void set_attribute (string_view key, std::string value);
    optional<std::string> attribute (string_view key);

    QRectF boundingRect () const override;
protected:
    explicit item(QObject *parent = 0);
    static void set_dash (QPainter* painter);

    /// overrides
    void paint (QPainter * painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void paint_attribute (QPainter* painter);
protected:
    qreal item_width = 100;
    qreal item_height = 0.8 * item_width;
    QString type_;
private:
    QString name_;
    QColor color_ = Qt::black;
    nlohmann::json item_info_;
signals:
    void name_changed (const QString&);
    void color_changed (const QColor&);

public slots:
};

%>

