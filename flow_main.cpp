#include "flow_main.h"
#include "ui_flow_main.h"
#include "drawer_list.h"

flow_main::flow_main(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::flow_main)
{
    ui->setupUi(this);
}

void flow_main::set_drawer(const QStringList& data)
{
    auto drawer_content = std::make_unique<drawer_list> (drawer_.get ());
    drawer_content->set_data (data);
    drawer_content->setMaximumWidth (60);
    drawer_content->setMinimumWidth (60);

    drawer_->setMaximumWidth (60);
    drawer_->setMinimumWidth (60);

    drawer_->setWidget (drawer_content.release ());

    drawer_->setAllowedAreas (Qt::LeftDockWidgetArea);
    addDockWidget (Qt::LeftDockWidgetArea, drawer_.get ());
}

flow_main::~flow_main()
{
    delete ui;
}
