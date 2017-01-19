#pragma once


#include "canvas/view.h"
#include "canvas/scene.h"
#include "utility/raii.hpp"

namespace canvas
<%

class body : public view
{
    Q_OBJECT
public:
    explicit body(QWidget* parent = nullptr, QString svg_dir = {});
    void file_new_tile();
    ///新文件命名标题
    void file_new_title();
    std::string dump();
    bool load (const std::string& data);
    QString get_path_from_name (const QString& name);
    void set_remark (const QString& remark);
    QString remark ();
    QString attached_file () { return windowTitle (); }
    void set_attached_file (QString attached_file) { setWindowTitle(attached_file); }
signals:
    void selection_changed ();
public slots:
    void window_modified();
private:
    void init_conn ();
private:
    canvas::scene scene_;

    QString cur_file_;
    bool is_untitled_;//文件未被保存
    QString svg_dir_;
    QString attached_file_;
};

%>
