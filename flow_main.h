#pragma once

#include <QMainWindow>
#include <QDockWidget>
#include <memory>
#include <QMdiArea>
#include <QToolBar>
#include "canvas/body.h"
#include "utility/interface.hpp"
#include "drawer/toolbox.h"
#include "attribute_widget.h"
#include <QWizardPage>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class flow_main;
}

class flow_main : public QMainWindow
{
    Q_OBJECT
public:
    explicit flow_main(QWidget *parent = nullptr);
    void set_drawer ();
    void set_attribute ();
    ~flow_main();


private slots:
    ///当窗口没有新建窗口是，显示为灰色
    void set_tool_action();

    void on_action_drawer_triggered();
    void on_action_print_triggered();

private:
    void set_mdi_area ();
    void init_conn ();
    void zoom_in_active ();
    void zoom_out_active ();

    void notify_attribute (bool ok);

private:
    void on_drawer_visibility_changed ();
    not_null<canvas::body*> create_canvas_body();
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
    canvas::body* active_canvas_body();
    /// 初始化右边属性栏
    void set_attribute_window ();
    /// 更新属性信息
    void update_remark ();

    void on_drawer_status (const QString& status);
    //获取向导页面
    //void get_new_page();
    //void get_future_page();
    //void get_improve_page();

private:
    Ui::flow_main *ui;
    std::unique_ptr<QDockWidget> drawer_ = std::make_unique<QDockWidget> (this);
    std::unique_ptr<drawer::toolbox> drawer_content_ = drawer::toolbox::make(this);

    std::unique_ptr<QDockWidget> attribute_ = std::make_unique<QDockWidget> (this);
    std::unique_ptr<attribute_widget> attribute_content_;

    QMdiArea *mdi_area_ = new QMdiArea (this);//是一个多文档显示窗口
    int sequence_number_ = 1;
    ///创建工具栏
private:
    QToolBar *toolbar_file = addToolBar(tr("文件"));
    QToolBar *toolbar_edit = addToolBar(tr("编辑"));
    //QWizardPage* new_create_page1();
    //QWizardPage* new_create_page2();
    //QWizardPage* new_create_page3();
    //QWizardPage* new_create_page4();
    //QWizardPage* new_create_page5();

    //QWizardPage* future_create_page1();
    //QWizardPage* future_create_page2();
    //QWizardPage* future_create_page3();
    //QWizardPage *future_create_page4();

    //QWizardPage* improve_create_page1();
    //QWizardPage* improve_create_page2();
    //QWizardPage* improve_create_page3();

    //QWizardPage *new_page_1 = new QWizardPage(this);
    //QWizardPage *new_page_2 = new QWizardPage(this);
    //QWizardPage *new_page_3 = new QWizardPage(this);
    //QWizardPage *new_page_4 = new QWizardPage(this);
    //QWizardPage *new_page_5 = new QWizardPage(this);

    //QWizardPage *future_page_1 = new QWizardPage(this);
    //QWizardPage *future_page_2 = new QWizardPage(this);
    //QWizardPage *future_page_3 = new QWizardPage(this);
    //QWizardPage *future_page_4 = new QWizardPage(this);

    //QWizardPage *improve_page_1 = new QWizardPage(this);
    //QWizardPage *improve_page_2 = new QWizardPage(this);
    //QWizardPage *improve_page_3 = new QWizardPage(this);

    //QVBoxLayout *new_layout_1 = new QVBoxLayout(this);
    //QVBoxLayout *new_layout_2 = new QVBoxLayout(this);
    //QVBoxLayout *new_layout_3 = new QVBoxLayout(this);
    //QVBoxLayout *new_layout_4 = new QVBoxLayout(this);
    //QVBoxLayout *new_layout_5 = new QVBoxLayout(this);

    //QVBoxLayout *future_layout_1 = new QVBoxLayout(this);
    //QVBoxLayout *future_layout_2 = new QVBoxLayout(this);
    //QVBoxLayout *future_layout_3 = new QVBoxLayout(this);
    //QVBoxLayout *future_layout_4 = new QVBoxLayout(this);

    //QVBoxLayout *improve_layout_1 = new QVBoxLayout(this);
    //QVBoxLayout *improve_layout_2 = new QVBoxLayout(this);
    //QVBoxLayout *improve_layout_3 = new QVBoxLayout(this);

    //QLabel *new_label_step_1 = new QLabel(this);
    //QLabel *new_label_title_1 = new QLabel(this);
    //QLabel *new_label_step_2 = new QLabel(this);
    //QLabel *new_label_title_2= new QLabel(this);
    //QLabel *new_label_step_3 = new QLabel(this);
    //QLabel *new_label_title_3= new QLabel(this);
    //QLabel *new_label_step_4 = new QLabel(this);
    //QLabel *new_label_title_4= new QLabel(this);
    //QLabel *new_label_step_5 = new QLabel(this);
    //QLabel *new_label_title_5= new QLabel(this);

    //QLabel *future_label_step_1 = new QLabel(this);
    //QLabel *future_label_title_1 = new QLabel(this);
    //QLabel *future_label_step_2 = new QLabel(this);
    //QLabel *future_label_title_2= new QLabel(this);
    //QLabel *future_label_step_3 = new QLabel(this);
    //QLabel *future_label_title_3= new QLabel(this);
    //QLabel *future_label_step_4 = new QLabel(this);
    //QLabel *future_label_title_4= new QLabel(this);

    //QLabel *improve_label_step_1 = new QLabel(this);
    //QLabel *improve_label_title_1 = new QLabel(this);
    //QLabel *improve_label_step_2 = new QLabel(this);
    //QLabel *improve_label_title_2= new QLabel(this);
    //QLabel *improve_label_step_3 = new QLabel(this);
    //QLabel *improve_label_title_3= new QLabel(this);
};
