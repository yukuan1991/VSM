#pragma once
#include <QPainter>
#include <QColor>
#include <memory>
#include <item/item.h>
#include <QPainterPath>
#include "item/fixed_item.h"
///信息
namespace item {


class information : public fixed_item
{
public:
    bool init ();
    static std::unique_ptr<information> make (json data, QPointF pos, item* parent);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    explicit information(json data, QPointF pos, item* parent = nullptr);
    qreal height() const { return fixed_item::height() / small_object_ratio_; }
private:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

};
}

