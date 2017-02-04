#ifndef polygon_H
#define polygon_H
#include <item/item.h>
#include <memory>//智能指针
///生产看板
namespace item {


class production_watcher_board : public item
{
public:
    static std::unique_ptr<production_watcher_board>make(QPointF pos, QColor color = Qt::black);

protected:
    explicit production_watcher_board(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1_ {0.01 * item_width, 0.0125 * item_height},
    p2_ {0.85 * item_width, 0.0125 * item_height},
    p3_ {0.99 * item_width, 0.2 * item_height},
    p4_ {0.99 * item_width, 0.9875 * item_height},
    p5_ {0.01 * item_width, 0.9875 * item_height};

};
}

#endif // polygon_H
