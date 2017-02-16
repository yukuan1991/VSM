#include "guide.h"
#include <QVBoxLayout>
#include <QLabel>
#include "qt-tools/video_widget.hpp"
#include "qt-tools/video_widget.hpp"

using infostr = tuple<QString, QString, QString>;
static const map<QString, vector<tuple<QString, QString, QString>>> guide_map
{
    {"current", { infostr {"第一步", "绘制顾客栏及参数", "第一步绘制顾客栏.mp4"}, infostr {"第二步", "绘制工作步骤及参数、库存三角", "第二步工作步骤与库存.mp4"}, infostr {"第三步", "画出供应商、物料流", "第三步供应商与物料流.mp4"}, infostr {"第四步","画出控制部门补充信息流", "第四步控制部门与信息流.mp4"}, infostr{"第五步","计算增值、非增值时间", "第五步增值时间.mp4"}} },
    {"future", { infostr {"第一步", "标出节拍时间（定拍单元）及之后工序和成品超市及发送到顾客过程（过程包括物流和看板信息流）", ""}, infostr {"第二步", "添加定拍单元前所有工序和原材料超市（包括物料流与看板信息流）", ""},
            infostr {"第三步","画出控制部门并补充所有信息流", ""}, infostr {"第四步","计算增值、非增值时间", ""} } },
    {"improve", { infostr {"第一步", "优化定拍环", ""}, infostr {"第二步", "优化定拍环之外其他环", ""}, infostr {"第三步","优化供应商环", ""} }}
};

static void start_wizard(const vector<tuple<QString, QString, QString>>& steps);
static unique_ptr<QWizardPage> create_page (const QString& step, const QString& title, const QString& video_path);

void invoke_guide(const QString &type)
{
    auto found = guide_map.find (type);
    if (found == guide_map.end ())
    {
        return;
    }

    start_wizard (found->second);
}

static void start_wizard(const vector<tuple<QString, QString, QString>>& steps)
{
    QWizard wizard_new;
    wizard_new.setWindowTitle("向导");
    wizard_new.setOption( QWizard::NoBackButtonOnStartPage );//设置第一页没有上一步的按钮
    wizard_new.setWizardStyle( QWizard::ModernStyle );//设置上一步下一步等按钮的显示格式

    for (auto & it : steps)
    {
        wizard_new.addPage(create_page(get<0> (it), get<1> (it), get<2> (it)).release ());
    }
    wizard_new.setMinimumWidth(800);
    wizard_new.setMinimumHeight(700);

    wizard_new.exec();
}

static unique_ptr<QWizardPage> create_page (const QString& step, const QString& title, const QString& video_path)
{
    auto page = make_unique<QWizardPage> ();
    page->setMinimumWidth(800);
    page->setMinimumHeight(600);

    page->setButtonText(QWizard::BackButton,"上一页");
    page->setButtonText(QWizard::NextButton,"下一页");
    page->setButtonText(QWizard::CancelButton,"取消");
    page->setButtonText(QWizard::FinishButton,"完成");

    auto layout = make_unique<QVBoxLayout> (page.get ());
    auto label_step = make_unique<QLabel> (step);
    auto label_title = make_unique<QLabel> (title);
    auto video = video_widget::make (video_path);
    video->setObjectName("video");
    layout->addWidget(label_step.release());
    layout->addWidget(label_title.release());
    layout->addWidget(video.release ());
    page->setLayout(layout.release());


    return page;
}

