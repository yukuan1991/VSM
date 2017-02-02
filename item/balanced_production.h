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


class balanced_production : public item
{

public:
    static std::unique_ptr<balanced_production> make (QPointF pos, QColor color = Qt::black);
protected:
    balanced_production(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
}

#endif // SQUARE_TEXT_H
