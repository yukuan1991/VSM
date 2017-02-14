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
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

};
}

#endif // information_H
