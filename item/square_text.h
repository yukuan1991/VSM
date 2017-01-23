#ifndef SQUARE_TEXT_H
#define SQUARE_TEXT_H
#include <item/item.h>
#include <QPainter>
#include <QPointF>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <memory>

///均衡生产
namespace item {


class square_text : public item
{

public:
    static std::unique_ptr<square_text> make (QPointF pos, QColor color = Qt::black);
protected:
    square_text(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    constexpr static qreal square_length=0.8 * item_width;
    constexpr static qreal square_heigth= 0.5 * item_height;
    constexpr static qreal text_square_length=0.3 * item_width ;
    constexpr static qreal text_square_heigth= 0.375 * item_height;
  };
}

#endif // SQUARE_TEXT_H
