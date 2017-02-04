
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

}

void signal_board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QPointF
    p1 {0.3 * item_width, 0.3125 * item_height},
    p2 {0.7 * item_width, 0.3125 * item_height},
    p3 {0.5 * item_width, 0.6875 * item_height};

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    painter->setPen(the_pen);

    painter->drawLine(p1,p2);
    painter->drawLine(p1,p3);
    painter->drawLine(p2,p3);

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
