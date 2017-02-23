#pragma once

#include <memory>
#include <item/item.h>
#include <QPointF>
#include <QColor>
#include "item/fixed_item.h"


///信号看板
namespace item {


class signal_board : public fixed_item
{
public:
    static std::unique_ptr<signal_board> make (json data, QPointF pos, item* parent);
    bool init ();
protected:
    signal_board(json data, QPointF pos, item* parent= nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    qreal height() const override { return height() / small_object_ratio_; }
    qreal width () const override { return width() / small_object_ratio_; }
private:

};

} /// end of item
