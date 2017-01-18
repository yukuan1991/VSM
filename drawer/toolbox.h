#pragma once

#include <QToolBox>
#include <memory>

class QDir;
namespace drawer
<%
class list;
class info_flow;

class toolbox : public QToolBox
{
    Q_OBJECT
signals:
    void status_changed (const QString&);
public:
    static std::unique_ptr<toolbox> make (const QString & entity_dir, const QString&, QWidget* parent = nullptr);
    ~toolbox () override;
protected:
    toolbox (QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags ());
    bool init (const QString & entity_dir, const QString&);
    QStringList get_file_names (const QDir& dir);
private:
    std::unique_ptr<list> entity_;
    std::unique_ptr<list> material_flow_;
    std::unique_ptr<info_flow> info_flow_;
};

%>
