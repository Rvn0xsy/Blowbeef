#pragma once
#include "modules.h"
class IPAddress :public Modules {
public:
	IPAddress(std::string tomlConfigFile);
	VOID HandleData();
};