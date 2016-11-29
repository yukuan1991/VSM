#include "main_widget.h"
#include "ui_main_widget.h"
#include <QWheelEvent>
#include <QMatrix>
#include <QGraphicsSvgItem>
#include "utility/raii.hpp"
#include <QLabel>
#include <QSvgRenderer>
#include <QSvgWidget>
#include <QDebug>
#include "utility/file.hpp"
#include <boost/locale.hpp>
#include <boost/filesystem.hpp>
#include "defs.hpp"

main_widget::main_widget(QWidget *parent, std::unique_ptr<QGraphicsScene> scene) :
        QWidget(parent),
        ui(std::make_unique<Ui::main_widget> ()),
        scene_ (std::move (scene))
{
    ui->setupUi(this);
    init_canvas ();
    init_drawer ();
    connect (ui->view, &canvas_view::scale_changed, ui->drawer, &drawer_list::set_scale);
}

main_widget::~main_widget()
{

}

void main_widget::init_canvas()
{
    ui->view->setScene (scene_.get ());
}

void main_widget::init_drawer()
{

}

