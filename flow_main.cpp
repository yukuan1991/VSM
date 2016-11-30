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
    connect(ui->action_file_new, SIGNAL(triggered()), this, SLOT(file_new()));


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
    qDebug () << __func__;
    canvs->show();

}

canvas_body *flow_main::create_canvas_body()
{
    canvas_body* canvas = new canvas_body();
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
