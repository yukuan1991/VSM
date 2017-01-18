#pragma once

#include <QListWidget>
#include "json.hpp"
#include "defs.hpp"
using namespace std::literals;
namespace drawer
<%

class list : public QListWidget
{
public:
    explicit list (QWidget* parent = nullptr);
    void set_data (const QStringList& data);
    void mousePressEvent (QMouseEvent* event) override;
    void set_scale (double scale) { view_scale_ = scale; }
private:
    double view_scale_ = 1.0;
    constexpr static auto path_role = Qt::UserRole + 100;
};

%>
