#include "text_item.h"
#include <QGraphicsSceneMouseEvent>
#include "utility/raii.hpp"


unique_ptr<text_item> text_item::make(QPointF point)
{
    auto ret = unique_ptr<text_item> (new text_item (point));

    if (ret == nullptr or !ret->init())
    {
        return nullptr;
    }

    return ret;
}

text_item::text_item(QPointF point)
{
    setPos (point);
}

bool text_item::init()
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    this->setPlainText("双击输入文字或数字");
    return true;
}

void text_item::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    SCOPE_EXIT { QGraphicsTextItem::mouseDoubleClickEvent(event); };
    if (textInteractionFlags() == Qt::NoTextInteraction)
    {
        setTextInteractionFlags(Qt::TextEditorInteraction);
    }
}

void text_item::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    QGraphicsTextItem::focusOutEvent(event);
    if (this->toPlainText().trimmed().isEmpty())
    {
        deleteLater();
    }
}
