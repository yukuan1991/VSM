#pragma once
#include <QGraphicsTextItem>
#include "utility/memory.hpp"


class text_item : public QGraphicsTextItem
{
public:
    static unique_ptr<text_item> make (QPointF point);
protected:
    text_item (QPointF point);
    bool init ();

    void mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) override;
    void focusOutEvent (QFocusEvent* event);
};

