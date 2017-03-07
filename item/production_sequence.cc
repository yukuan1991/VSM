#include "production_sequence.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QInputDialog>
///修改完成
namespace item {


std::unique_ptr<production_sequence>production_sequence::make(json data, QPointF pos, abstract_item* parent)
{
    std::unique_ptr <production_sequence> ret(new production_sequence(::move(data), pos, parent));
    if(!ret->init ())
    {
        return nullptr;

    }
    else
    {
        return ret;
    }
}

production_sequence::production_sequence(json data, QPointF pos, abstract_item* parent)
    :fixed_item(::move(data), pos, parent)
{   

}

bool production_sequence::init()
{
    set_item_type("生产工序");

    enable_attribute  ("周期时间");
    enable_attribute ("换模时间");
    enable_attribute ("设备开机率");
    enable_attribute ("产品批量大小");
    enable_attribute ("操作工数量");
    enable_attribute ("产品类别");
    enable_attribute ("包装数量");
    enable_attribute ("工作时间");
    enable_attribute ("不良品");

    set_z_value(301);

    return true;

}

void production_sequence::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SCOPE_EXIT { fixed_item::paint(painter, option, widget); };
    Q_UNUSED(widget);

    auto item_width = width();
    auto item_height = height();
    QPointF
    p1_ {0.01 * item_width, 0.0125 * item_height},
    p3_ {0.01 * item_width, 0.35 * item_height},
    p4_ {0.99 * item_width, 0.35 * item_height},
    p6_ {0.99 * item_width, 0.9875 * item_height};


    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(item_width * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawRect(QRectF (p1_,p6_));
    painter->drawLine(p3_,p4_);
    auto item_name = name();
    if(item_name.empty())
    {
        return;
    }

    QFontMetricsF metrics (painter->font());
    auto text_width = metrics.width(item_name.data());
    auto text_height = metrics.height();
    auto center = QRectF (p1_, p4_).center();
    painter->drawText(QRectF (center - QPointF (text_width / 2, text_height / 2), QSizeF (text_width, text_height)), item_name.data());
}

void production_sequence::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED (event);
    auto old_name = name ();
    bool confirmed = false;
    auto company_name = QInputDialog::getText(nullptr, "", "名称:",
                                              QLineEdit::Normal, old_name.data(), &confirmed);
    if (confirmed)
    {
        set_name (company_name.trimmed ().toStdString());
    }

}
}
