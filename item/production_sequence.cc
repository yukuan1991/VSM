#include "production_sequence.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QInputDialog>
///修改完成
namespace item {


std::unique_ptr<production_sequence>production_sequence::make(QPointF pos, QColor color)
{
    std::unique_ptr <production_sequence> ret(new production_sequence);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "生产工序";
    return ret;
}

production_sequence::production_sequence(item* parent)
    :item(parent)
{   
     set_attribute ("周期时间");
     set_attribute("换模时间");
     set_attribute("设备开机率");
     set_attribute("产品批量大小");
     set_attribute("操作工数量");
     set_attribute("产品类别");
     set_attribute("包装数量");
     set_attribute("工作时间");
     set_attribute("不良品");

     set_z_value(301);
}

void production_sequence::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SCOPE_EXIT { item::paint(painter, option, widget); };
    Q_UNUSED(widget);

    QPointF
    p1_ {0.01 * item_width_, 0.0125 * item_height_},
    p3_ {0.01 * item_width_, 0.35 * item_height_},
    p4_ {0.99 * item_width_, 0.35 * item_height_},
    p6_ {0.99 * item_width_, 0.9875 * item_height_};


    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidthF(item_width_ * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawRect(QRectF (p1_,QSizeF ((p6_ - p1_).x(), (p6_ - p1_).y())));
    painter->drawLine(p3_,p4_);
    auto item_name = name();
    if(item_name.empty())
    {
        return;
    }

    QFontMetricsF metrics (painter->font());
    auto width = metrics.width(item_name.data());
    auto height = metrics.height();
    auto center = QPointF (item_width_ / 2, (p6_.y() + p4_.y()) / 2);
    painter->drawText(QRectF (center - QPointF (width / 2, height / 2), QSizeF (width, height)), item_name.data());
}

void production_sequence::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
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
