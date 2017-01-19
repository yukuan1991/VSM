﻿#pragma once


#include <QObject>
#include <QGraphicsItem>
#include "utility/raii.hpp"
#include "json.hpp"

namespace item
<%

class item : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:


    const QString& name () { return name_; }
    void set_name (QString s) { name_ = ::move (s);  emit name_changed (name_); }
    const QColor& color () { return color_; }
    void set_color (QColor c) { color_ = ::move (c); emit color_changed (c); }
    virtual bool set_data (const nlohmann::json& data)  { Q_UNUSED (data); return true; }

protected:
    explicit item(QObject *parent = 0);
    static void set_dash (QPainter* painter);

    /// overrides
    void paint (QPainter * painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect () const override;

protected:
    constexpr static qreal item_width = 100;
    constexpr static qreal item_height = 0.8 * item_width;
private:
    QString name_;
    QColor color_ = Qt::black;
signals:
    void name_changed (const QString&);
    void color_changed (const QColor&);

public slots:
};

%>
