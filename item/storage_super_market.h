#ifndef supermarket_rectangles_H
#define supermarket_rectangles_H
#include <item/item.h>
#include <memory>

///库存超市
namespace item {


class storage_super_market : public item
{
public:
   static std::unique_ptr<storage_super_market> make(QPointF pos,QColor color);

protected:
    storage_super_market(item* parent = nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:


  };
}

#endif // supermarket_rectangles_H
