#ifndef FLOW_MAIN_H
#define FLOW_MAIN_H

#include <QMainWindow>
#include <QDockWidget>
#include <memory>
#include <QMdiArea>
#include "drawer_list.h"
#include "canvas_body.h"

namespace Ui {
class flow_main;
}

class flow_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit flow_main(QWidget *parent = 0);
    void set_drawer (const QStringList& data);
    ~flow_main();


private slots:
    void on_drawer_visibility_changed ();

    void on_action_drawer_triggered();
    ///新建文件
    void file_new();
    canvas_body *create_canvas_body();
private:
    void set_mdi_area ();
    void init_conn ();

private:
    Ui::flow_main *ui;
    std::unique_ptr<QDockWidget> drawer_ = std::make_unique<QDockWidget> (this);
    std::unique_ptr<drawer_list> drawer_content_ = std::make_unique<drawer_list> (drawer_.get ());

    QMdiArea *mdi_area_ = new QMdiArea (this);//是一个多文档显示窗口
};

#endif // FLOW_MAIN_H
