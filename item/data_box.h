#ifndef data_box_H
#define data_box_H
#include <item/item.h>
#include <memory>
#include <utility>
#include "utility/containers.hpp"

///数据箱
namespace item {

using std::tuple;
using std::make_tuple;
using std::get;

class data_box : public item
{
public:
    static std::unique_ptr<data_box> make(QPointF pos,QColor color);
protected:
    data_box(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    optional<tuple<string, string, string, string>> set_box_data (string a, string b, string c, string d);


  };
}
#endif // data_box_H
