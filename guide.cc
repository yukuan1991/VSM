#include "guide.h"
#include <QVBoxLayout>
#include <QLabel>

static const map<QString, vector<pair<QString, QString>>> guide_map
{
    {"new", { {"123", "456"}, {"234", "567"} } },
    {"improve", { {"123", "456"}, {"234", "567"} } },
    {"future", { {"123", "456"}, {"234", "567"} } }
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

