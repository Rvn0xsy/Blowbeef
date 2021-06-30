#pragma once
#include "modules.h"
class DISK_Volume :
    public Modules
{
    public:
        DISK_Volume(std::string tomlConfigFile);
        VOID HandleData();
};

