#ifndef OTHER_COMPANY_H
#define OTHER_COMPANY_H
#include "item/item.h"
#include "item/fixed_item.h"

namespace item {


class other_company : public fixed_item
{
public:
    bool init ();
    static std::unique_ptr<other_company> make (json data, QPointF pos, item* parent);
protected:
    other_company(json data, QPointF pos, item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};
}
#endif // OTHER_COMPANY_H
