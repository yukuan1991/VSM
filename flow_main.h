#ifndef FLOW_MAIN_H
#define FLOW_MAIN_H

#include <QMainWindow>
#include <QDockWidget>
#include <memory>
#include <QMdiArea>
#include <QToolBar>
#include "drawer_list.h"
#include "canvas_body.h"
#include "remark_widget.h"

namespace Ui {
class flow_main;
}

class flow_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit flow_main(QWidget *parent = nullptr);
    void set_drawer (const QStringList& data);
    ~flow_main();


private slots:
    ///当窗口没有新建窗口是，显示为灰色
    void set_tool_action();

    void on_action_drawer_triggered();
private:
    void set_mdi_area ();
    void init_conn ();
    void zoom_in_active ();
    void zoom_out_active ();

    void set_attribute ();

private:
    void on_drawer_visibility_changed ();
    canvas_body *create_canvas_body();
    /// 新建文件
    void file_new();
    /// 打开文件
    void file_open ();
    /// 保存文件
    void file_save ();
    /// 另存为
    void file_save_as ();
    ///新建工具栏
    void create_toolbar();
    ///查看活动窗口
    canvas_body* active_canvas_body();
    /// 初始化右边属性栏
    void set_attribute_window ();
    /// 更新属性信息
    void update_remark ();


private:
    Ui::flow_main *ui;
    std::unique_ptr<QDockWidget> drawer_ = std::make_unique<QDockWidget> (this);
    std::unique_ptr<drawer_list> drawer_content_ = std::make_unique<drawer_list> (drawer_.get ());

    std::unique_ptr<QDockWidget> attribute_ = std::make_unique<QDockWidget> (this);
    std::unique_ptr<remark_widget> attribute_content_ = std::make_unique<remark_widget> (this);

    QMdiArea *mdi_area_ = new QMdiArea (this);//是一个多文档显示窗口
    int sequence_number_ = 1;
    ///创建工具栏
private:
    QToolBar *toolbar_file = addToolBar(tr("文件"));
    QToolBar *toolbar_edit = addToolBar(tr("编辑"));

};

#endif // FLOW_MAIN_H
