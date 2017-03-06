#include "text_item.h"
#include <QGraphicsSceneMouseEvent>
#include "utility/raii.hpp"
#include <QGraphicsScene>
#include <QDialog>
#include <QLineEdit>
#include <QPainter>
#include <QInputDialog>
#include <QStyleOptionGraphicsItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

namespace item {

unique_ptr<text_item> text_item::make(json data, QPointF pos, abstract_item *parent)
{
    auto ret = unique_ptr<text_item> (new text_item (::move (data), pos, parent));

    if (ret == nullptr or ! ret->init ())
    {
        return nullptr;
    }
    return ret;
}

text_item::text_item(nlohmann::json data, QPointF pos, item::abstract_item *parent)
    :abstract_item (::move (data), pos, parent)
{

}

bool item::text_item::init() try
{
    string text = json_find (dump (), "text");
    text_ = text.data ();

    QFontMetricsF metrics (font_);
    const auto text_w = metrics.width (text_);
    const auto text_h = metrics.height ();

    const auto rect = QRectF (0, 0, text_w, text_h);

    bounding_rect_ = rect;
    shape_.addRect (rect);

    return true;
}
catch (const std::exception &)
{
    return false;
}

void text_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setFont (font_);
    painter->drawText (bounding_rect_, text_);



    if (option->state bitand QStyle::State_Selected)
    {
        auto pen = painter->pen ();
        pen.setStyle (Qt::DashLine);
        pen.setWidthF (1.0);
        painter->setPen (pen);

        painter->drawRect (bounding_rect_);
    }
}

QRectF text_item::boundingRect() const
{
    return bounding_rect_;
}

QPainterPath text_item::shape() const
{
    return shape_;
}

unique_ptr<QDialog> text_item::make_modify_dialog()
{
    auto dlg = make_unique<QDialog> ();

    auto v_layout = make_unique<QVBoxLayout> ();

    auto line_edit = make_unique<QLineEdit> (dlg.get ());

    v_layout->addWidget (line_edit.get ());

    auto h_layout = make_unique<QHBoxLayout> ();
    auto button_ok = make_unique<QPushButton> ("确定");
    v_layout->addLayout (h_layout.release ());

    dlg->setLayout (v_layout.release ());
    return nullptr;
}

void text_item::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    abstract_item::mouseDoubleClickEvent (event);
    auto ok = false;
    auto text = QInputDialog::getText (nullptr, "输入文字", "文字内容", QLineEdit::Normal, text_, &ok);

    if (!ok)
    {
        return;
    }

    text_ = ::move (text);
    dump () ["text"] = text_.toStdString ();

    QFontMetricsF metrics (font_);
    const auto text_w = metrics.width (text_);
    const auto text_h = metrics.height ();

    const auto rect = QRectF (0, 0, text_w, text_h);

    bounding_rect_ = rect;
    shape_ = QPainterPath ();
    shape_.addRect (rect);

    if (text_.trimmed ().isEmpty ())
    {
        deleteLater ();
    }
    else
    {
        update ();
    }
}

}
