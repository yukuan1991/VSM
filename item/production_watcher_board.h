#ifndef polygon_H
#define polygon_H
#include <item/item.h>
#include <memory>//智能指针
#include "item/fixed_item.h"
#include
///生产看板
namespace item {


class production_watcher_board : public fixed_item
{
public:
    static std::unique_ptr<production_watcher_board>make(QPointF pos, QColor color = Qt::black);

protected:
    explicit production_watcher_board(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:

};
}

#endif // polygon_H
