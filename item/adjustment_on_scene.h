#pragma once
#include "item/item.h"
#include <memory>
///现场调度
namespace item {

class adjustment_on_scene : public item
{
public:
    static std::unique_ptr<adjustment_on_scene> make(QPointF pos, QColor = Qt::black);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    adjustment_on_scene(item* parent = nullptr);
private:


};
}
