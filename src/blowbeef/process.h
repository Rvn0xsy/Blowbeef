#pragma once
#include "modules.h"
class Process:public Modules {
	public:
		Process(std::string tomlConfigFile);
		VOID HandleData();
};