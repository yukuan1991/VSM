#pragma once

#include <QWidget>
#include <vector>
#include <initializer_list>
#include <memory>

namespace Ui {
class info_flow;
}

class QVBoxLayout;
class QPushButton;

namespace drawer
<%
class info_flow : public QWidget
{
    Q_OBJECT
signals:
    void status_changed (const QString&);
public:
    static std::unique_ptr<info_flow> make (QWidget* parent = nullptr,
                                            const std::initializer_list<QString>& buttons = {});
    QString status ();
    bool set_status (const QString& status);
    ~info_flow() override;
protected:
    bool init (const std::initializer_list<QString>& buttons);
    explicit info_flow(QWidget *parent = 0);
    //void hideEvent
    void hideEvent(QHideEvent *event) override;
private:
    void button_clicked ();
private:
    QVBoxLayout *verticalLayout;
    std::vector<QPushButton*> buttons_;
};

%>
