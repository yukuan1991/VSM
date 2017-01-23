#ifndef VS_ITEM_CONVEY_H
#define VS_ITEM_CONVEY_H
#include <item/item.h>
#include <memory>
////操作员
namespace item {


class convey : public item
{
public:
    static std::unique_ptr <convey> make(QPointF pos,QColor color = Qt::black);

protected:
    convey(item* parent = nullptr);
     void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    int startAngle = 1.9 * item_width * 16;
    int spanAngle = 1.6 * item_width * 16;
    constexpr static qreal x = 0.15*item_width;///20
    constexpr static qreal y = 0.20*item_height; ///20
    constexpr static qreal width = 0.7*item_width;
    constexpr static qreal heigth = 0.75*item_height;
    QPointF
    p1 {0.1  * item_width, 0.2125 * item_height},
    p2 {0.7 * item_width, 0.2125 * item_height};


  };
}

#endif // VS_ITEM_CONVEY_H
