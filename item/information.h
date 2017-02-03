#ifndef information_H
#define information_H
#include <QPainter>
#include <QColor>
#include <memory>
#include <item/item.h>
#include <QPainterPath>
///信息
namespace item {


class information : public item
{
public:
    static std::unique_ptr<information> make (QPointF pos, QColor color = Qt::black);
protected:
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    explicit information(item* parent = nullptr);

private:
    constexpr static qreal information_length=0.8 * item_width;
    constexpr static qreal information_heigth= 0.5 * information_length;
   };
}

#endif // information_H
