#ifndef data_box_H
#define data_box_H
#include <item/item.h>
#include <memory>

///数据箱
namespace item {


class data_box : public item
{
public:
    static std::unique_ptr<data_box> make(QPointF pos,QColor color);
protected:
    data_box(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:


  };
}
#endif // data_box_H
