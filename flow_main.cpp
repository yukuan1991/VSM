#include "flow_main.h"
#include "ui_flow_main.h"
#include <QDebug>
#include "canvas_body.h"
#include <QAction>
#include "utility/raii.hpp"
#include <QFileDialog>
#include <QMessageBox>
#include <QMdiSubWindow>
#include "utility/file.hpp"
#include <QDebug>
#include <QMdiSubWindow>

flow_main::flow_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::flow_main)
{
    ui->setupUi(this);
    create_toolbar();
     //更新活动窗口
    connect (mdi_area_, &QMdiArea::subWindowActivated, this, &flow_main::set_tool_action);
    set_tool_action();
    set_mdi_area ();
    init_conn ();
    set_attribute_window ();
}

void flow_main::set_attribute_window()
{
    attribute_content_->setMaximumWidth (60);
    attribute_content_->setMinimumWidth (60);

    attribute_->setMaximumWidth (60);
    attribute_->setMinimumWidth (60);

    attribute_->setWidget (attribute_content_.get());

    attribute_->setAllowedAreas (Qt::RightDockWidgetArea);
    addDockWidget (Qt::RightDockWidgetArea, attribute_.get ());
}

void flow_main::update_remark()
{
    auto remark = attribute_content_->remark();
    auto canvas = active_canvas_body();
    if (canvas == nullptr)
    {
        return;
    }

    canvas->set_remark(remark);
}

void flow_main::set_drawer(const QStringList& data)
{
    drawer_content_->set_data (data);
    drawer_content_->setMaximumWidth (60);
    drawer_content_->setMinimumWidth (60);

    drawer_->setMaximumWidth (60);
    drawer_->setMinimumWidth (60);

    drawer_->setWidget (drawer_content_.get ());

    drawer_->setAllowedAreas (Qt::LeftDockWidgetArea);
    addDockWidget (Qt::LeftDockWidgetArea, drawer_.get ());
}

flow_main::~flow_main()
{
    delete ui;
}

void flow_main::file_new()
{
    canvas_body *canvas = create_canvas_body();
    canvas->show();
}

void flow_main::file_open()
{
    auto file_name = QFileDialog::getOpenFileName(this, "打开文件", ".", "Images (*.fc)");
    if (file_name.isEmpty())
    {
        return;
    }

    auto file_content = ::read_all(::utf_to_sys(file_name.toStdString()).data());
    if (!file_content)
    {
        QMessageBox::information(this, "打开", "打开文件失败，请检查文件是否存在");
        return;
    }

    auto canvas = create_canvas_body();
    if (!canvas->load (*file_content))
    {
        QMessageBox::information(this, "打开", "打开文件失败，文件已经损坏");
        return;
    }
}

void flow_main::file_save()
{
    auto sub_window = mdi_area_->activeSubWindow();
    if (sub_window == nullptr)
    {
        QMessageBox::information(this, "保存", "暂无可保存数据");
        return;
    }

    auto path = QFileDialog::getSaveFileName(this, "文件保存", ".", "Flow format (*.fc");
    if (path.isEmpty())
    {
        return;
    }

    auto w = dynamic_cast<canvas_body*> (sub_window->widget()); assert(w);
    ::write_buffer (::utf_to_sys(path.toStdString()).data(), w->dump());
}

void flow_main::create_toolbar()
{
    toolbar_file->addActions({ui->action_file_new,ui->action_file_open,ui->action_file_save,ui->action_file_save_other});
    toolbar_file->addSeparator();///添加一条分割线
    toolbar_edit->addActions({ui->action_zoom_in,ui->action_zoom_out, ui->action_drawer});
}

canvas_body* flow_main::active_canvas_body()
{
    if(QMdiSubWindow *active_subwindow = mdi_area_->activeSubWindow())
    {
        canvas_body *canvas_ptr = dynamic_cast<canvas_body*> (active_subwindow->widget());
        assert (canvas_ptr);
        return canvas_ptr;
    }
    else
    {
        return nullptr;
    }
}


void flow_main::set_tool_action()
{
    bool has_canvas_body = (active_canvas_body() != nullptr);

    ui->action_file_save->setEnabled(has_canvas_body);
    ui->action_file_save_other->setEnabled(has_canvas_body);
    ui->action_file_save_other->setEnabled(has_canvas_body);
    ui->action_zoom_in->setEnabled(has_canvas_body);
    ui->action_zoom_out->setEnabled(has_canvas_body);
    ui->action_back_out->setEnabled(has_canvas_body);

    ui->action_file_new->setEnabled(true);
    ui->action_file_open->setEnabled(true);
}


canvas_body *flow_main::create_canvas_body()
{
    auto canvas = std::make_unique<canvas_body> (mdi_area_, SVG_DIR);
    auto raw_canvas = canvas.get ();

    canvas->setAttribute (Qt::WA_DeleteOnClose);
    canvas->setWindowState(Qt::WindowMaximized);
    mdi_area_->addSubWindow(canvas.release ());

    connect(raw_canvas, &canvas_body::selection_changed, this, &flow_main::set_attribute);

    return raw_canvas;
}

void flow_main::set_mdi_area()
{
    mdi_area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi_area_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdi_area_);
    mdi_area_->setViewMode (QMdiArea::TabbedView);
}

void flow_main::init_conn()
{
    connect (drawer_.get (), &QDockWidget::visibilityChanged, [this] (bool){ on_drawer_visibility_changed (); });
    connect(ui->action_file_new, &QAction::triggered, this, &flow_main::file_new);
    connect(ui->action_file_open, &QAction::triggered, this, &flow_main::file_open);
    connect(ui->action_file_save, &QAction::triggered, this, &flow_main::file_save);
    connect (ui->action_zoom_in, &QAction::triggered, this, &flow_main::zoom_in_active);
    connect (ui->action_zoom_out, &QAction::triggered, this, &flow_main::zoom_out_active);
    connect(attribute_content_.get (), &remark_widget::text_changed, this, &flow_main::update_remark);
}

void flow_main::zoom_in_active()
{
    auto active_canvas = active_canvas_body(); assert (active_canvas);

    active_canvas->scale_object(1.1);
}

void flow_main::zoom_out_active()
{
    auto active_canvas = active_canvas_body(); assert (active_canvas);
    active_canvas->scale_object(1 / 1.1);
}

void flow_main::set_attribute()
{
    auto active_canvas = active_canvas_body(); assert (active_canvas);

    auto remark = active_canvas->remark();
    attribute_content_->set_remark(remark);
}

void flow_main::on_drawer_visibility_changed()
{
    ui->action_drawer->setChecked (!drawer_->isHidden ());
}

void flow_main::on_action_drawer_triggered()
{
    if (ui->action_drawer->isChecked ())
    {
        drawer_->show ();
    }
    else
    {
        drawer_->hide ();
    }
}

