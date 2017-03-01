#pragma once
#include "item/item.h"


namespace item {

class arrow_item : public item::item
{
public:
    static unique_ptr<arrow_item> make (json data, item* parent = nullptr);
protected:
    explicit arrow_item (json data, QPointF pos, item* parent);
    bool init ();
    QPointF p1 () { return p1_; }
    QPointF p2 () { return p2_; }
    static tuple<QPointF, QPointF> get_pos (const json & data);
private:
    QPointF p1_, p2_;
};

} // namespace item


