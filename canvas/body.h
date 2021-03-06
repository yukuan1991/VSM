﻿#pragma once


#include "canvas/view.h"
#include "canvas/scene.h"
#include "utility/raii.hpp"
#include "utility/memory.hpp"
#include <QPrinter>
class QPrinter;

namespace canvas
<%

class body : public view
{
    Q_OBJECT
public:
    explicit body(QWidget* parent = nullptr, QString svg_dir = {});
    void file_new_tile(); ///新文件命名标题
    void file_new_title();
    std::string dump();
    bool load (const std::string& data);
    QString get_path_from_name (const QString& name);
    void set_remark (const QString& remark);
    QString remark ();
    QString attached_file () { return windowTitle (); }
    void set_attached_file (QString attached_file) { setWindowTitle(attached_file); }
    const nlohmann::json selected_item_data ();
    void set_item_attribute (string_view key, std::string value = {});
    void print_render (QPrinter* printer);
    ~body ();
signals:
    void selection_changed (bool);
public slots:
    void window_modified();
private:
    void init_conn ();
private:
    canvas::scene scene_;

    QString cur_file_;
    bool is_untitled_;
    //文件未被保存
    QString svg_dir_;
    QString attached_file_;
};

%>
