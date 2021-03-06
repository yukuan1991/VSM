﻿
#include "signal_board.h"
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
///修改成了1/4
namespace item
<%


signal_board::signal_board(json data, QPointF pos, abstract_item *parent)
    :fixed_item (::move(data), pos, parent)
{

}

bool signal_board::init()
{
    enable_attribute ("生产批量");

    set_z_value(315);
    set_item_type("信号看板");

    return true;

}

void signal_board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    auto item_width_ = width();
    auto item_height_ = height();
    QPointF
    p1 {0.05 * item_width_, item_height_ / 80},
    p2 {0.95 * item_width_, item_height_ / 80},
    p3 {0.5 * item_width_, 79 * item_height_ / 80};

    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF (std::max (item_width_ * 0.02, 2.0));
    painter->setPen(the_pen);

    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1, p2, p3}}, Qt::WindingFill);

    fixed_item::paint(painter, option, widget);

}

std::unique_ptr<signal_board> signal_board::make(json data, QPointF pos, abstract_item* parent)
{
    std::unique_ptr <signal_board> ret (new signal_board(::move(data), pos, parent));
    if(!ret->init ())
    {
        return nullptr;

    }
    else
    {
        return ret;
    }

}
%>
