#ifndef data_box_H
#define data_box_H
#include <item/item.h>
#include <memory>
#include <QVBoxLayout>
#include "MultiInputDialog.h"

///数据箱
namespace item {


class data_box : public item
{
public:
    static std::unique_ptr<data_box> make(QPointF pos,QColor color);
protected:
    data_box(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void add_widget();
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label_1 = new QLabel(tr("名称1"));
    QLabel * label_2 = new QLabel(tr("名称2"));
    QLabel * label_3 = new QLabel(tr("名称2"));
    QLabel * label_4 = new QLabel(tr("名称2"));
    QLineEdit * edit_1 = new QLineEdit;
    QLineEdit * edit_2  = new QLineEdit;
    QLineEdit * edit_3  = new QLineEdit;
    QLineEdit * edit_4  = new QLineEdit;


  };
}
#endif // data_box_H
