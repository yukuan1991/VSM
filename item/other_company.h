#ifndef OTHER_COMPANY_H
#define OTHER_COMPANY_H
#include "item/item.h"

namespace item {


class other_company : public item
{
public:
    static std::unique_ptr<other_company> make (QPointF pos, QColor color = Qt::black);
protected:
    other_company(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};
}
#endif // OTHER_COMPANY_H
