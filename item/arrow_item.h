#pragma once
#include "item/abstract_item.h"


namespace item {

class arrow_item : public abstract_item::abstract_item
{
public:
    static unique_ptr<arrow_item> make (json data, abstract_item* parent = nullptr);
protected:
    explicit arrow_item (json data, QPointF pos, abstract_item* parent);
    bool init ();
    QPointF p1 () { return p1_; }
    QPointF p2 () { return p2_; }
    qreal angle () { return angle_; }
    qreal radius () { return radius_; }
    QPointF start_pos () { return start_pos_; }
    QPointF stop_pos () { return stop_pos_; }
    static tuple<QPointF, QPointF> get_pos (const json & data);
private:
    QPointF p1_, p2_;
    QPointF start_pos_, stop_pos_;
    qreal angle_;
    qreal radius_;
};

} // namespace item


