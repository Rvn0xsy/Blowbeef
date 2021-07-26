#pragma once
#include <toml.hpp>
#include <exception>
#include "WMIC.h"

class Modules
{
	public:
		VOID Query();
		VOID Release();
		TableData* GetData();
	protected:
		VOID SetModuleName(std::string str);
		VOID SetWMIDescription(std::string str);
		VOID SetWMIQuery(std::string str);
		VOID SetWMINameSpace(std::string str);
		WMIQueryer* Queryer;
		toml::value module;
		std::string moduleName;
		std::string moduleWMIDescription;
		std::string moduleWMIQuery;
		std::string moduleWMINameSpace;
		std::vector<std::string> moduleWMIKey;
		TableData * moduleQueryResultData;
};
