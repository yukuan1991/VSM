#include "board_info_flow.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
namespace item {


unique_ptr<board_info_flow> board_info_flow::make(vector<unique_ptr<QGraphicsLineItem> > tmp_lines, QColor color, item *parent)
{
    unique_ptr <board_info_flow> ret (new board_info_flow (parent));
    ret->set_color(std::move(color));
    ret->type_ = "看板用信息流";

    if (! ret->init(::move (tmp_lines)))
    {
        return nullptr;
    }
    return ret;
}

board_info_flow::board_info_flow(item* parent)
    :item(parent)
{
    set_z_value(103);
}

bool board_info_flow::init(vector<unique_ptr<QGraphicsLineItem> > tmp_lines)
{
    if (tmp_lines.empty ())
    {
        return false;
    }

    auto begin_ptr = tmp_lines.front()->line().p1();
    setPos(begin_ptr);
    lines_.reserve(tmp_lines.size ());
    for (auto & it : tmp_lines)
    {
        lines_.emplace_back (it->line().p1() - begin_ptr, it->line().p2() - begin_ptr);
    }

    return true;
}

void board_info_flow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED (option);
    Q_UNUSED (widget);
    auto lines = this->lines_;
    if (lines.empty())
    {
        return;
    }

    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor (color ());

    if (option->state bitand QStyle::State_Selected)
    {
        pen.setColor(Qt::red);
    }
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);

    painter->setBrush(color ());

    auto last_line = lines.back ();
    lines.pop_back ();

    for (auto & it : lines)
    {
        painter->drawLine (it);
    }

    auto arrow_length = last_line.length ();
    auto body_length = arrow_length - tip_length;
    auto body_end = QLineF {last_line.p1(), last_line.p2 ()}.pointAt(body_length / arrow_length);
    auto vertical_line = QLineF (body_end, last_line.p1 ()).normalVector();

    auto neck1 = vertical_line.pointAt(tip_width / vertical_line.length());
    auto neck2 = vertical_line.pointAt(- tip_width / vertical_line.length());

    painter->drawLine(last_line.p1 (), body_end);
    pen.setWidthF(1);
    painter->drawPolygon({{neck1, neck2, last_line.p2 ()}}, Qt::WindingFill);
}

QRectF board_info_flow::boundingRect() const
{
    return {-20, -20, 40, 40};
}

}
