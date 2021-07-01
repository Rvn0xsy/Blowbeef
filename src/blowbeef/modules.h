#pragma once
#include <toml.hpp>
#include <exception>
#include "WMIC.h"

class Modules
{
	public:
		BOOL ParseTomlConfig();
		VOID SetModuleName(std::string moduleName);
		VOID SetTomlConfigFile(std::string tomlConfigFile);
		VOID Query();
		VOID HandleData();
		VOID Release();
	protected:
		int GetFilterKeyIndex();
		WMIQueryer* Queryer;
		toml::value module;
		std::string tomlConfigFile;
		std::string moduleName;
		std::string moduleDescription;
		std::string moduleWMIQuery;
		std::string moduleWMINameSpace;
		std::string moduleWMIFilterKey;
		std::vector<std::string> moduleWMIKey;
		std::vector<std::string> moduleWMIFilter;
		TableData * moduleQueryResultData;
};
