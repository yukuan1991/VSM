#ifndef CIRCLE_H
#define CIRCLE_H
#include <memory>
#include <QPointF>
#include <QColor>
#include <QRectF>
#include "item/item.h"
///取料

namespace item {


class improve : public item
{
public:
    static std::unique_ptr<improve> make(QPointF pos, QColor color = Qt::black);

protected:
    explicit improve(item* parent=nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
//    int startAngle = 1 * item_width * 16;
//    int spanAngle = 1.7 * item_width * 16;
//    constexpr static qreal x = 0.2 * item_width;///20
//    constexpr static qreal y = 0.25 * item_height; ///20
//    constexpr static qreal width = 0.8 * item_width;
//    constexpr static qreal heigth = 0.75 * item_height;

    QPointF
    p1 {50, 60},
    p2 {40,55};
   // p3 {40,55};

};


}
#endif // CIRCLE_H
