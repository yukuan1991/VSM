#include "guide.h"
#include <QVBoxLayout>
#include <QLabel>

static const map<QString, vector<pair<QString, QString>>> guide_map
{
    {"current", { {"第一步", "绘制顾客栏及参数"}, {"第二步", "绘制工作步骤及参数、库存三角"}, {"第三步", "画出供应商、物料流"},{"第四步","画出控制部门补充信息流"},{"第五步","计算增值、非增值时间"}} },
    {"future", { {"第一步", "标出节拍时间（定拍单元）及之后工序和成品超市及发送到顾客过程（过程包括物流和看板信息流）"}, {"第二步", "添加定拍单元前所有工序和原材料超市（包括物料流与看板信息流）"},
            {"第三步","画出控制部门并补充所有信息流"},{"第四步","计算增值、非增值时间"} } },
    {"improve", { {"第一步", "优化定拍环"}, {"第二步", "优化定拍环之外其他环"}, {"第三步","优化供应商环"} }}
};

static void start_wizard(const vector<pair<QString, QString>>& steps);
static unique_ptr<QWizardPage> create_page (const QString& step, const QString& title);


void invoke_guide(const QString &type)
{
    auto found = guide_map.find (type);
    if (found == guide_map.end ())
    {
        return;
    }

    start_wizard (found->second);
}

static void start_wizard(const vector<pair<QString, QString>>& steps)
{
    QWizard wizard_new;
    wizard_new.setWindowTitle("wizardialog");
    wizard_new.setOption( QWizard::NoBackButtonOnStartPage );//设置第一页没有上一步的按钮
    wizard_new.setWizardStyle( QWizard::ModernStyle );//设置上一步下一步等按钮的显示格式

    for (auto & it : steps)
    {
        wizard_new.addPage(create_page(it.first, it.second).release ());
    }

    wizard_new.exec();
}

static unique_ptr<QWizardPage> create_page (const QString& step, const QString& title)
{
    auto page = make_unique<QWizardPage> ();

    page->setButtonText(QWizard::BackButton,"上一页");
    page->setButtonText(QWizard::NextButton,"下一页");
    page->setButtonText(QWizard::CancelButton,"取消");
    page->setButtonText(QWizard::FinishButton,"完成");

    auto layout = make_unique<QVBoxLayout> (page.get ());
    auto label_step = make_unique<QLabel> (step);
    auto label_title = make_unique<QLabel> (title);
    layout->addWidget(label_step.release());
    layout->addWidget(label_title.release());
    page->setLayout(layout.release());

    return page;
}

