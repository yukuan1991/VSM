#ifndef square_H
#define square_H
#include <QPainter>
#include <QColor>
#include <memory>
#include <item/item.h>
#include <QPainterPath>
///信息
namespace item {


class square : public item
{
public:
    static std::unique_ptr<square> make (QPointF pos, QColor color = Qt::black);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    explicit square(item* parent = nullptr);

private:
    constexpr static qreal square_length=0.8 * item_width;
    constexpr static qreal square_heigth= 0.5 * square_length;
   };
}

#endif // square_H
