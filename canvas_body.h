#ifndef CANVAS_BODY_H
#define CANVAS_BODY_H

#include "canvas_view.h"
#include "canvas_scene.h"

class canvas_body : public canvas_view
{
    Q_OBJECT
public:
    canvas_body(QWidget* parent = nullptr, QString svg_dir = {});
    void file_new_tile();
    std::string dump();
    bool load (const std::string& data);
    QString get_path_from_name (const QString& name);
    void set_remark (const QString& remark);
    QString remark ();
signals:
    void selection_changed ();
private:
    void init_conn ();
private:
    canvas_scene scene_;

    QString cur_file_;
    bool is_untitled_;//文件未被保存
    QString svg_dir_;
};

#endif // CANVAS_BODY_H
