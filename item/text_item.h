#pragma once
#include <QGraphicsTextItem>
#include "utility/memory.hpp"
#include "item/abstract_item.h"
#include <QFont>

namespace item {

class text_item : public abstract_item
{
public:
    static unique_ptr<text_item> make (json data, QPointF pos, abstract_item* parent = nullptr);
protected:
    text_item (json data, QPointF pos, abstract_item * parent);
    bool init ();
    void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QRectF boundingRect () const override;
    QPainterPath shape () const override;
    unique_ptr<QDialog> make_modify_dialog ();

    void mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) override;
private:
    QRectF bounding_rect_;
    QPainterPath shape_;
    QString text_;
    QFont font_;
};

}
