#include "other_company.h"
#include "QStyleOptionGraphicsItem"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QAction>
#include <QMenu>
#include <QInputDialog>

namespace item {


std::unique_ptr<other_company> other_company::make(QPointF pos, QColor color)
{
    std::unique_ptr <other_company> ret(new other_company);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "其他公司";
    return ret;
}

other_company::other_company(item * parent)
    :item(parent)
{
    set_attribute("需求量");
    set_attribute("包装方式");
    set_attribute("工作班数");
    set_z_value(302);
}

void other_company::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SCOPE_EXIT { item::paint(painter, option, widget); };

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);

    auto x_scale = item_width_ / 100;
    auto y_scale =item_height_ / 80;
    const QPointF
            p1 {1 * x_scale, 30 * y_scale},
    p2 {33 * x_scale,1 * y_scale},
    p3 {33 * x_scale,26 * y_scale},
    p4 {66 * x_scale,1 * y_scale},
    p5 {66 * x_scale,26 * y_scale},
    p6 {99 * x_scale,4 * y_scale},
    p7 {99 * x_scale,79 * y_scale},
    p8 {1 * x_scale,79 * y_scale};
    painter->drawPolygon({{p1,p2,p3,p4,p5,p6,p7,p8}},Qt::WindingFill);

    auto item_name = name ();
    if (item_name.empty())
    {
        return;
    }

    QFontMetricsF metrics (painter->font());
    auto width = metrics.width(item_name.data());
    auto height = metrics.height();
    auto center = QPointF (item_width_ / 2, (p1.y() + p8.y()) / 2);
    painter->drawText(QRectF (center - QPointF (width / 2, height / 2),
                              QSizeF (width, height)), item_name.data());
}


void other_company::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED (event);
    auto old_name = name ();
    bool confirmed = false;
    QInputDialog dlg;
    dlg.setInputMode (QInputDialog::TextInput);
    dlg.setLabelText("公司名称");
    dlg.move(QCursor::pos() - QPoint (dlg.width() / 2, dlg.height() / 2));
    if (dlg.exec() == QInputDialog::Accepted)
    {
        set_name(dlg.textValue().trimmed().toStdString());
    }
    //auto company_name = QInputDialog::getText(nullptr, "", "公司名称:",
    //                                          QLineEdit::Normal, old_name.data(), &confirmed);
    //if (confirmed)
    //{
    //    set_name (company_name.trimmed ().toStdString());
    //}
}

}
