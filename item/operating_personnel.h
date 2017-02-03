#ifndef VS_ITEM_CONVEY_H
#define VS_ITEM_CONVEY_H
#include <item/item.h>
#include <memory>
////操作员
namespace item {


class operating_personnel : public item
{
public:
    static std::unique_ptr <operating_personnel> make(QPointF pos,QColor color = Qt::black);

protected:
    operating_personnel(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
}

#endif // VS_ITEM_CONVEY_H
