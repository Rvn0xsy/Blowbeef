#pragma once
#include "modules.h"
class NetRoute :
    public Modules
{
public:
    NetRoute(std::string tomlConfigFile);
    VOID HandleData();
};

