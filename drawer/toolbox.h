#pragma once

#include <QToolBox>
#include <memory>

class QDir;
namespace drawer
<%
class list;
class info_flow;
class drag_widget;

class toolbox : public QToolBox
{
    Q_OBJECT
signals:
    void status_changed (const QString&);
public:
    static std::unique_ptr<toolbox> make (QWidget* parent);
    QString status ();
    ~toolbox () override;
protected:
    toolbox (QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags ());
    bool init ();
    static std::unique_ptr<drag_widget> init_entity ();
    static std::unique_ptr<drag_widget> init_material_flow ();
    QStringList get_file_names (const QDir& dir);
private:
};

%>
