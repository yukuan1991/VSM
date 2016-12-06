#ifndef CANVAS_BODY_H
#define CANVAS_BODY_H

#include "canvas_view.h"
#include "canvas_scene.h"

class canvas_body : public canvas_view
{
public:
    canvas_body(QWidget* parent = nullptr);
    void file_new_tile();
    std::string dump();
private:
    canvas_scene scene_;

    QString cur_file_;
    bool is_untitled_;//文件未被保存
};

#endif // CANVAS_BODY_H
