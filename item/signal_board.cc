
#include "signal_board.h"
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

namespace item
<%


signal_board::signal_board(item *parent)
    :item (parent)
{
    set_attribute("生产批量");

}

void signal_board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QPointF
    p1 {0.05 * item_width, item_height / 80},
    p2 {0.95 * item_width, item_height / 80},
    p3 {0.5 * item_width, 79 * item_height / 80};

    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * item_width);
    painter->setPen(the_pen);

    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1, p2, p3}}, Qt::WindingFill);

    item::paint(painter, option, widget);

}

std::unique_ptr<signal_board> signal_board::make(QPointF pos, QColor color)
{
    std::unique_ptr <signal_board> ret (new signal_board);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "信号看板";
    return ret;

}
%>
