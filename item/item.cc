#include "item.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPen>

namespace item
<%

item::item(QObject *parent) : QObject(parent)
{
    setFlags (ItemIsSelectable | ItemIsMovable);
    set_data({
                 {{"卡车运输", "注明运输频率"}},
                 {{"yyyyyyyyyyyyyyyyyyyyyy", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"}}
             });
}

void item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    if (option->state bitand QStyle::State_Selected)
    {
        set_dash(painter);
        painter->drawRect (boundingRect ());
    }

    QFontMetricsF metrix (painter->font ());
    auto h_scale = metrix.height ();
    qreal width = 0;
    qreal height = 0;
    QString qstr = {};

    for (auto& iter : item_info_)
    {
        std::string key = iter.begin().key();
        std::string content = iter.begin().value();
        qstr += (key + " : " + content + "\n").data ();
        height += h_scale;
    }
    qstr.chop (1);
    auto rect = boundingRect ();
    QRectF text_rect (rect.left (), rect.bottom (), width, height);
    painter->drawText(text_rect, qstr, Qt::AlignCenter | Qt::AlignVCenter);
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

%> // namespace item
