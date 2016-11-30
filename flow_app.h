#pragma once

#include "qt-tools/application.h"
#include <main_widget.h>

class flow_app : public application
{
public:
    flow_app(int argc, char** argv);
    bool run () override;
private:
    std::unique_ptr<main_widget> main_;
};

