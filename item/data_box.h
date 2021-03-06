﻿#pragma once
#include <item/abstract_item.h>
#include <memory>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <utility>
#include "utility/containers.hpp"
#include "item/fixed_item.h"

///数据箱
namespace item {

using std::tuple;
using std::make_tuple;
using std::get;

class data_box : public fixed_item
{
public:
    static std::unique_ptr<data_box> make(json data, QPointF pos,abstract_item* parent);
    bool init ();
protected:
    data_box(json data, QPointF pos, abstract_item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
//public slots:
//    void get_edit_text();

private:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    optional<tuple<string, string, string, string>> set_box_data (string a, string b, string c, string d);


  };
}
