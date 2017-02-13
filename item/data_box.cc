#include "data_box.h"
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
///数据箱
   ///修改完成
namespace item {


data_box::data_box(item* parent)
    :item (parent)
{
    set_z_value(303);
   // connect(button_ok, SIGNAL(clicked()), this, SLOT(get_edit_text()));

}

void data_box::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget);

    QPointF
    p1_ {0.01* item_width_, 0.0125 * item_height_},
    p2_ {0.99 * item_width_, 0.0125 * item_height_},
    p3_ {0.01 * item_width_, 0.25 * item_height_},
    p4_ {0.99 * item_width_, 0.25 * item_height_},
    p5_ {0.01 * item_width_, 0.5 * item_height_},
    p6_ {0.99 * item_width_, 0.5 * item_height_},
    p7_ {0.01 * item_width_, 0.7375 * item_height_},
    p8_ {0.99 * item_width_, 0.7375 * item_height_},
    p9_ {0.01 * item_width_, 0.9875 * item_height_},
    p10_ {0.99 * item_width_, 0.9875 * item_height_};

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidthF(item_width_ * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_, p2_, p10_, p9_}},Qt::WindingFill);
    painter->drawLine(p5_,p6_);
    painter->drawLine(p7_,p8_);
    painter->drawLine(p3_,p4_);
    auto item_name = name();
    if(item_name.empty())
    {
        return;
    }

    QFontMetricsF metrics (painter->font());
    auto width = metrics.width(item_name.data());
    auto height = metrics.height();
    auto center_1 = QPointF (item_width_ / 2, (p1_.y() + p3_.y() ) / 2);
    auto center_2 = QPointF (item_width_ / 2, (p5_.y() + p7_.y() ) / 2);
    auto center_3 = QPointF (item_width_ / 2, (p3_.y() + p5_.y() ) / 2);
    auto center_4 = QPointF (item_width_ / 2, (p7_.y() + p9_.y() ) / 2);

    painter->drawText(QRectF (center_3 - QPointF (width / 2, height / 2), QSizeF (width, height)), item_name.data());
    painter->drawText(QRectF (center_1 - QPointF (width / 2, height / 2), QSizeF (width, height)), item_name.data());
    painter->drawText(QRectF (center_2 - QPointF (width / 2, height / 2), QSizeF (width, height)), item_name.data());
    painter->drawText(QRectF (center_4 - QPointF (width / 2, height / 2), QSizeF (width, height)), item_name.data());



    item::paint(painter, option, widget);
}

//void data_box::get_edit_text()
//{

//    auto text_1 = label_1->text().toStdString();
//    auto text_2 = label_2->text().toStdString();
//    auto text_3 = label_3->text().toStdString();
//    auto text_4 = label_4->text().toStdString();
//    qDebug() << "text_";

//}

void data_box::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
//    auto old_name = name ();
//    bool confirmed = false;
//    auto name_1 = QInputDialog::getText(nullptr, "", "名称:",
//                                              QLineEdit::Normal, old_name.data(), &confirmed);

//    if (confirmed)
//    {
//        set_name (name_1.trimmed ().toStdString());
    //    }

//    add_widget();


}
// data_box::~data_box()
//{
//     delete widget;
//     qDebug () << "删除创建的对象";

//}

//void data_box::add_widget()
//{
//     label_1->setFixedSize(30,20);
//     label_2->setFixedSize(30,20);
//     label_3->setFixedSize(30,20);
//     label_4->setFixedSize(30,20);

//    button_ok->setFixedSize(40,20);
//    button_cancle->setFixedSize(40,20);
//    button_ok->setText(tr("确定"));
//    button_cancle->setText(tr("取消"));
//    edit_1->setFixedSize(200,20);
//    edit_2->setFixedSize(200,20);
//    edit_3->setFixedSize(200,20);
//    edit_4->setFixedSize(200,20);

//    layout_->addWidget(label_1);
//    layout_->addWidget(edit_1);
//    layout_1->addWidget(label_2);
//    layout_1->addWidget(edit_2);
//    layout_2->addWidget(label_3);
//    layout_2->addWidget(edit_3);
//    layout_3->addWidget(label_4);
//    layout_3->addWidget(edit_4);
//    layout_4->addWidget(button_ok);
//    layout_4->addWidget(button_cancle);
//    vb_layout->addLayout(layout_);
//    vb_layout->addLayout(layout_1);
//    vb_layout->addLayout(layout_2);
//    vb_layout->addLayout(layout_3);
//    vb_layout->addLayout(layout_4);
//    widget->setLayout(vb_layout);

//    widget->setMaximumSize(400,400);
//    widget->show();


//}

//std::tuple<std::string, std::string, std::string, std::string> data_box::get_names(const std::tuple<std::string, std::string, std::string, std::string> &old_value)
//{

//}

std::unique_ptr<data_box> data_box::make(QPointF pos, QColor color)
{
    std::unique_ptr<data_box> ret(new data_box);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "数据箱";
    return ret;
 }
}
