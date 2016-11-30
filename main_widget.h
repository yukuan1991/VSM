#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QString>
#include <QGraphicsScene>
#include <memory>
#include <vector>

namespace Ui {
class main_widget;
}

class main_widget : public QWidget
{
    Q_OBJECT

public:
    explicit main_widget(QWidget *parent = nullptr, std::unique_ptr<QGraphicsScene> scene = std::make_unique<QGraphicsScene> ());
    ~main_widget();
    void set_drawer (const QStringList& data);
private: /// UI
    void init_canvas ();
private:
    std::unique_ptr<Ui::main_widget> ui;
    std::unique_ptr<QGraphicsScene> scene_;

    std::vector<std::string> svg_files_ {
        "电子信息流",
        "改善点-大",
        "均衡生产",
        "看板",
        "看板盒",
        "客户供应商",
        "库存",
        "拉动",
        "流程",
        "数据盒",
        "推动",
        "外部运输",
        "先进先出",
        "超市"
    };
};

#endif // MAIN_WIDGET_H
