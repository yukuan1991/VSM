#ifndef FIFO_H
#define FIFO_H
#include "item/item.h"


namespace item {

class fifo : public item
{
public:
    static std::unique_ptr<fifo> make(QPointF pos, QColor = Qt::black);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    fifo (item* parent = nullptr);
};

} // namespace item

#endif // FIFO_H
