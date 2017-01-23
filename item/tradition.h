#ifndef VS_ITEM_ELECTRON_H
#define VS_ITEM_ELECTRON_H
#include <vs_item.h>
#include <memory>

///传统信息流
namespace item {


class vs_item_tradition : public vs_item
{
public:
    static std::unique_ptr <vs_item_tradition> make(QPointF pos, QColor color = Qt::black);
protected:
    vs_item_electron(vs_item* parent =nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF
    p1{0.8 * item_width, 0.46875 * item_height},///a
    p2{0.35 * item_width, 0.46875 * item_height},///b
    p3{0.35 * item_width,0.4375 * item_height},///c1
    p4{0.3 * item_width, 0.46875 * item_height},///c2
    p5{0.35 * item_width,0.5 * item_height};///c3
};

}

#endif // VS_ITEM_ELECTRON_H
