#include "item.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPen>

namespace item {

item::item(QObject *parent) : QObject(parent)
{
    setFlags (ItemIsSelectable | ItemIsMovable);
}

void item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    if (option->state bitand QStyle::State_Selected)
    {
        set_dash(painter);
        painter->drawRect (boundingRect ());
    }
}

QRectF item::boundingRect() const
{
    return {0, 0, item_width, item_height};
}

void item::set_dash(QPainter *painter)
{
    painter->setBrush(Qt::transparent);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
}

} // namespace item
