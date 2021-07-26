#include "QuickFixEngineering.h"

QuickFixEngineering::QuickFixEngineering()
{
	this->SetModuleName("QuickFixEngineering");
	this->SetWMIDescription("HotFix");
	this->SetWMINameSpace("ROOT\\CIMV2");
	this->SetWMIQuery("select HotFixID,InstalledOn from Win32_QuickFixEngineering");
	this->moduleWMIKey = std::vector<std::string>{ "HotFixID","InstalledOn" };

}
