﻿#ifndef FLOW_MAIN_H
#define FLOW_MAIN_H

#include <QMainWindow>
#include <QDockWidget>
#include <memory>
#include <QMdiArea>
#include <QToolBar>
#include "drawer_list.h"
#include "canvas_body.h"

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
    void on_drawer_visibility_changed ();

    void set_tool_action();///当窗口没有新建窗口是，显示为灰色

    void on_action_drawer_triggered();
private:
    void set_mdi_area ();
    void init_conn ();

private:
    canvas_body *create_canvas_body();
    /// 新建文件
    void file_new();
    void file_open ();
    void file_save ();
    ///新建工具栏
    void create_toolbar();
    canvas_body* activity_canvas_body();///查看活动窗口


private:
    Ui::flow_main *ui;
    std::unique_ptr<QDockWidget> drawer_ = std::make_unique<QDockWidget> (this);
    std::unique_ptr<drawer_list> drawer_content_ = std::make_unique<drawer_list> (drawer_.get ());

    QMdiArea *mdi_area_ = new QMdiArea (this);//是一个多文档显示窗口
    int sequence_number_ = 1;
    ///创建工具栏
private:
    QToolBar *toolbar_file = addToolBar(tr("文件"));
    QToolBar *toolbar_edit = addToolBar(tr("编辑"));

};

#endif // FLOW_MAIN_H
