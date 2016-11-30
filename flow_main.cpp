#include "flow_main.h"
#include "ui_flow_main.h"
#include <QDebug>
#include "canvas_body.h"
#include <QAction>

flow_main::flow_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::flow_main)
{
    ui->setupUi(this);
    mdi_area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi_area_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdi_area_);

    connect (drawer_.get (), &QDockWidget::visibilityChanged, [this] (bool){ on_drawer_visibility_changed (); });
    connect (ui->action_file_new, &QAction::triggered, this, &flow_main::file_new);
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
    canvas_body *canvs = create_canvas_body();
  //  file_new _tile(canvs);
    canvs->show();

}

//flow_main::file_new_tile(canvas_body *window)
//{
//    is_untitled_ = true;//设置为未命名
//    cur_file_ = tr("图片文档 %1").arg(sequence_number_);//将当前文件命名为文档加编号的形式
//    sequence_number_++;

//    setWindowTitle(cur_file_ + "[*]"+ tr("echo"));//文档被改之后显示*这个标志被修改
//}

canvas_body *flow_main::create_canvas_body()
{
    canvas_body* canvas = new canvas_body(mdi_area_);
    mdi_area_->addSubWindow(canvas);
    canvas->setWindowState(Qt::WindowMaximized);//使得创建的新窗口默认为最大化
    return canvas;
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
