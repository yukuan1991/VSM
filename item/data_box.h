#ifndef data_box_H
#define data_box_H
#include <item/item.h>
#include <memory>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

///数据箱
namespace item {


class data_box : public item
{
public:
    static std::unique_ptr<data_box> make(QPointF pos,QColor color);
    ~data_box();
protected:
    data_box(item* parent = nullptr);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
//public slots:
//    void get_edit_text();

private:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
   // void add_widget();

    std::tuple<std::string, std::string, std::string, std::string>
    get_names (const std::tuple<std::string, std::string, std::string, std::string>& old_value);

//    QWidget *widget = new QWidget;

//    QHBoxLayout *layout_ = new QHBoxLayout;
//    QHBoxLayout *layout_1 = new QHBoxLayout;
//    QHBoxLayout *layout_2 = new QHBoxLayout;
//    QHBoxLayout *layout_3 = new QHBoxLayout;
//    QHBoxLayout *layout_4 = new QHBoxLayout;
//    QVBoxLayout *vb_layout = new QVBoxLayout;


//    QLabel *label_1 = new QLabel(tr("名称1"));
//    QLineEdit * edit_1 = new QLineEdit;
//    QLabel * label_2 = new QLabel(tr("名称2"));
//    QLineEdit * edit_2  = new QLineEdit;
//    QLabel * label_3 = new QLabel(tr("名称3"));
//    QLineEdit * edit_3  = new QLineEdit;
//    QLabel * label_4 = new QLabel(tr("名称4"));
//    QLineEdit * edit_4  = new QLineEdit;

//    QPushButton *button_ok = new QPushButton;
//    QPushButton *button_cancle = new QPushButton;


  };
}
#endif // data_box_H
