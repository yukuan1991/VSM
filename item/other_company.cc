#include "other_company.h"
#include "QStyleOptionGraphicsItem"
#include "QPainter"
#include <QGraphicsSceneMouseEvent>
#include <QAction>
#include <QMenu>
#include <QInputDialog>

namespace item {


bool other_company::init()
{
    set_item_type("其他公司");

    set_attribute("需求量");
    set_attribute("包装方式");
    set_attribute("工作班数");

    set_z_value(302);

    return true;
}

std::unique_ptr<other_company> other_company::make(nlohmann::json data, QPointF pos, abstract_item *parent)
{
    std::unique_ptr <other_company> ret(new other_company (::move (data), pos, parent));
    if(!ret->init ())
    {
        return nullptr;
    }
    else
    {
        return ret;
    }

}

other_company::other_company(json data, QPointF pos, abstract_item * parent)
    :fixed_item(::move(data), pos, parent)
{

}

void other_company::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SCOPE_EXIT { fixed_item::paint(painter, option, widget); };
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    painter->setBrush(Qt::white);
    auto x_scale = width() / 100;
    auto y_scale = height() / 80;
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
    auto text_width = metrics.width(item_name.data());
    auto text_height = metrics.height();
    auto center = QPointF (x_scale * 50, (p1.y() + p8.y()) / 2);
    painter->drawText(QRectF (center - QPointF (text_width / 2, text_height / 2),
                              QSizeF (text_width, text_height)), item_name.data());
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
