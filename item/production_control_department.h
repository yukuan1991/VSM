#ifndef PRODUCTION_CONTROL_DEPARTMENT_H
#define PRODUCTION_CONTROL_DEPARTMENT_H
#include "item/item.h"

///生产控制部门
namespace item {


class production_control_department : public item
{
public :
    static std::unique_ptr<production_control_department> make(QPointF pos, QColor color = Qt::black);
protected:
    production_control_department(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void paint_attribute (QPainter* painter) override;
};
}
#endif // PRODUCTION_CONTROL_DEPARTMENT_H
