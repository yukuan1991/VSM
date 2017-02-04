
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
    return ret;

}
%>
