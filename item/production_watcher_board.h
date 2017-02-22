#ifndef polygon_H
#define polygon_H
#include <item/item.h>
#include <memory>
#include "item/fixed_item.h"
///生产看板
namespace item {

class production_watcher_board : public fixed_item
{
public:
    static std::unique_ptr<production_watcher_board>make(json data, QPointF pos, item* parent);
    bool init ();
protected:
    explicit production_watcher_board(json data, QPointF pos, item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:

};
}

#endif // polygon_H
