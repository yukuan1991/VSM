#pragma once

#include "qt-tools/application.h"
#include <flow_main.h>

class flow_app : public application
{
public:
    using INT = int;
    explicit flow_app(int argc, char** argv);
    bool run () override;
private:
    void exec_update (std::vector<std::pair<std::string, std::string>>);
    void update_check ();
private:
    std::unique_ptr<flow_main> main_;
};

