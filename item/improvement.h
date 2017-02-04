#pragma once

#include <memory>
#include <QPointF>
#include <QColor>
#include <QRectF>
#include "item/item.h"
///改善

namespace item {


class improvement : public item
{
public:
    static std::unique_ptr<improvement> make(QPointF pos, QColor color = Qt::black);

protected:
    explicit improvement(item* parent=nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:


};

}
