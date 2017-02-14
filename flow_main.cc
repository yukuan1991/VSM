﻿#include "flow_main.h"
#include "ui_flow_main.h"
#include <QDebug>
#include "canvas/body.h"
#include <QAction>
#include "utility/raii.hpp"
#include <QFileDialog>
#include <QMessageBox>
#include <QMdiSubWindow>
#include "utility/file.hpp"
#include <QDebug>
#include <QMdiSubWindow>
#include <QWizardPage>
#include <QPrintDialog>
#include <QHBoxLayout>

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
    set_attribute ();
}

void flow_main::set_attribute_window()
{
    attribute_->setWidget (attribute_content_.get());
    connect(attribute_content_.get (), &attribute_widget::commit, [this]
    {
        auto active_canvas = this->active_canvas_body();
        auto changes = attribute_content_->apply();
        for (auto & it : changes)
        {
            active_canvas->set_item_attribute (it.first, it.second);
        }
    });
    if (attribute_->isHidden())
    {
        attribute_->show();
    }
}

void flow_main::update_remark()
{
    auto canvas = active_canvas_body();

    if (canvas == nullptr)
    {
        return;
    }
}

void flow_main::on_drawer_status(const QString &status)
{
    Q_UNUSED(status);
}

void flow_main::get_page()
{
    QWizard *wizard_ = new QWizard(this);
    wizard_->setWindowTitle("wizardialog");
    wizard_->setOption( QWizard::NoBackButtonOnStartPage );//设置第一页没有上一步的按钮
    wizard_->setWizardStyle( QWizard::ModernStyle );//设置上一步下一步等按钮的显示格式
    wizard_->addPage(create_page1());
    wizard_->addPage(create_page2());
    wizard_->addPage(create_page3());
    wizard_->addPage(create_page4());
    wizard_->addPage(create_page5());
    wizard_->exec();
}

QWizardPage *flow_main::create_page1()
{

        page_1->setButtonText(QWizard::BackButton,"上一页");
        page_1->setButtonText(QWizard::NextButton,"下一页");
        page_1->setButtonText(QWizard::CancelButton,"取消");
        page_1->setButtonText(QWizard::FinishButton,"完成");
        label_step_1->setText(tr("第一步"));
        label_title_1->setText(tr("绘制顾客栏及参数"));
        layout_1->addWidget(label_step_1);
        layout_1->addWidget(label_title_1);
        page_1->setLayout(layout_1);
        return page_1;
}

QWizardPage *flow_main::create_page2()
{
    page_2->setButtonText(QWizard::BackButton,"上一页");
    page_2->setButtonText(QWizard::NextButton,"下一页");
    page_2->setButtonText(QWizard::CancelButton,"取消");
    page_2->setButtonText(QWizard::FinishButton,"完成");
    label_step_2->setText(tr("第二步"));
    label_title_2->setText(tr("绘制工作步骤及参数、库存三角"));
    layout_2->addWidget(label_step_2);
    layout_2->addWidget(label_title_2);
    page_2->setLayout(layout_2);
    return page_2;

}

QWizardPage *flow_main::create_page3()
{
    page_3->setButtonText(QWizard::BackButton,"上一页");
    page_3->setButtonText(QWizard::NextButton,"下一页");
    page_3->setButtonText(QWizard::CancelButton,"取消");
    page_3->setButtonText(QWizard::FinishButton,"完成");
    label_step_3->setText(tr("第三步"));
    label_title_3->setText(tr("画出供应商、物料流"));
    layout_3->addWidget(label_step_3);
    layout_3->addWidget(label_title_3);
    page_3->setLayout(layout_3);
    return page_3;
}

QWizardPage *flow_main::create_page4()
{
    page_4->setButtonText(QWizard::BackButton,"上一页");
    page_4->setButtonText(QWizard::NextButton,"下一页");
    page_4->setButtonText(QWizard::CancelButton,"取消");
    page_4->setButtonText(QWizard::FinishButton,"完成");
    label_step_4->setText(tr("第四步"));
    label_title_4->setText(tr("画出控制部门补充信息流"));
    layout_4->addWidget(label_step_4);
    layout_4->addWidget(label_title_4);
    page_4->setLayout(layout_4);
    return page_4;

}

QWizardPage *flow_main::create_page5()
{
    page_5->setButtonText(QWizard::BackButton,"上一页");
    page_5->setButtonText(QWizard::NextButton,"下一页");
    page_5->setButtonText(QWizard::CancelButton,"取消");
    page_5->setButtonText(QWizard::FinishButton,"完成");
    label_step_5->setText(tr("第五步"));
    label_title_5->setText(tr("计算增值、非增值时间"));
    layout_5->addWidget(label_step_5);
    layout_5->addWidget(label_title_5);
    page_5->setLayout(layout_5);
    return page_5;

}

void flow_main::set_drawer()
{
    drawer_->setMaximumWidth (150);
    drawer_->setMinimumWidth (150);
    drawer_content_->setMaximumWidth (140);
    drawer_content_->setMinimumWidth (140);

    drawer_->setWidget (drawer_content_.get ());
    connect(drawer_content_.get (), &drawer::toolbox::status_changed, this, &flow_main::on_drawer_status);

    drawer_->setAllowedAreas (Qt::LeftDockWidgetArea);
    addDockWidget (Qt::LeftDockWidgetArea, drawer_.get ());
}

void flow_main::set_attribute()
{
    attribute_->setMaximumWidth(250);
    attribute_->setMinimumWidth(250);
    attribute_->setAllowedAreas (Qt::RightDockWidgetArea);
    addDockWidget (Qt::RightDockWidgetArea, attribute_.get ());
}

flow_main::~flow_main()
{
    delete ui;
}

void flow_main::file_new()
{
    canvas::body *canvas = create_canvas_body();
    canvas->file_new_title();
    canvas->show();
}

void flow_main::file_open()
{
    auto file_name = QFileDialog::getOpenFileName(this, "打开文件", ".", "Images (*.vsm)");
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

    canvas->set_attached_file(::move (file_name));
}

void flow_main::file_save()
{
    auto sub_window = mdi_area_->activeSubWindow();
    assert (sub_window);

    auto w = dynamic_cast<canvas::body*> (sub_window->widget()); assert(w); ///获取到当前要保存的窗口

    QString path;
    if (w->attached_file().isEmpty())
    {
        path = QFileDialog::getSaveFileName(this, "文件保存", ".", "Value Stream Mapping (*.vsm");
        if (path.isEmpty())
        {
            return;
        }
    }
    else
    {
        path = w->attached_file();
    }

    ///这里进行判断
    ::write_buffer (::utf_to_sys(path.toStdString()).data(), w->dump());
    w->set_attached_file(::move (path));
}

void flow_main::file_save_as()
{
    auto sub_window = mdi_area_->activeSubWindow();
    assert (sub_window);

    auto w = dynamic_cast<canvas::body*> (sub_window->widget()); assert(w); ///获取到当前要保存的窗口

    auto path = QFileDialog::getSaveFileName(this, "文件保存", ".", "Value Stream Mapping (*.vsm");
    if (path.isEmpty())
    {
        return;
    }
    ::write_buffer (::utf_to_sys(path.toStdString()).data(), w->dump());

    w->set_attached_file (path);
}

void flow_main::create_toolbar()
{
    toolbar_file->addActions({ui->action_file_new,ui->action_file_open,ui->action_file_save,ui->action_file_save_as});
    toolbar_file->addSeparator();///添加一条分割线
    toolbar_edit->addActions({ui->action_zoom_in,ui->action_zoom_out,ui->action_all_zoom_back,ui->action_all_zoom_in, ui->action_drawer});
}

canvas::body* flow_main::active_canvas_body()
{
    if(QMdiSubWindow *active_subwindow = mdi_area_->activeSubWindow())
    {
        canvas::body *canvas_ptr = dynamic_cast<canvas::body*> (active_subwindow->widget());
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
    ui->action_file_save_as->setEnabled(has_canvas_body);
    ui->action_zoom_in->setEnabled(has_canvas_body);
    ui->action_zoom_out->setEnabled(has_canvas_body);
    ui->action_back_out->setEnabled(has_canvas_body);

    ui->action_file_new->setEnabled(true);
    ui->action_file_open->setEnabled(true);
}


not_null<canvas::body*> flow_main::create_canvas_body()
{
    auto canvas = std::make_unique<canvas::body> (mdi_area_, SVG_DIR);
    auto raw_canvas = canvas.get ();

    canvas->setAttribute (Qt::WA_DeleteOnClose);
    canvas->setWindowState(Qt::WindowMaximized);
    mdi_area_->addSubWindow(canvas.release ());

    connect(raw_canvas, &canvas::body::selection_changed, this, &flow_main::notify_attribute);
    connect (drawer_content_.get(), &drawer::toolbox::status_changed,
             raw_canvas, &canvas::body::set_arrow_state);

    connect (raw_canvas, &canvas::body::arrow_finished, drawer_content_.get(), &drawer::toolbox::reset_status);

    raw_canvas->set_arrow_state(drawer_content_->status ());

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
    connect(ui->action_file_save_as, &QAction::triggered, this, &flow_main::file_save_as);
    connect (ui->action_zoom_in, &QAction::triggered, this, &flow_main::zoom_in_active);
    connect (ui->action_zoom_out, &QAction::triggered, this, &flow_main::zoom_out_active);

    connect(ui->action_new_guide, &QAction::triggered, this, &flow_main::get_page);
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

void flow_main::notify_attribute(bool ok)
{
    attribute_->setWidget (nullptr);
    if (!ok)
    {
        return;
    }
    auto active_canvas = active_canvas_body();
    if (active_canvas == nullptr)
    {
        return;
    }

    auto attribute = active_canvas->selected_item_data();
    if (attribute.size() == 0)
    {
        return;
    }

    attribute_content_  = attribute_widget::make (::move (attribute), this);

    set_attribute_window ();
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

void flow_main::on_action_print_triggered()
{
    auto body = active_canvas_body ();
    if (body == nullptr)
    {
        QMessageBox::information (this, "打印", "没有选中的窗口");
        return;
    }
    QPrinter printer;
    printer.setPageOrientation (QPageLayout::Orientation::Landscape);
    QPrintDialog dlg (&printer);
    if (QPrintDialog::Accepted == dlg.exec ())
    {
        body->print_render (&printer);
    }
}
