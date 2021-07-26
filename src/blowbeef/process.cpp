#include "process.h"

Process::Process()
{
    this->SetModuleName("Process");
	this->SetWMIDescription("Process");
	this->SetWMINameSpace("root\\cimv2");
	this->SetWMIQuery("select Name,Handle from win32_process");
	this->moduleWMIKey = std::vector<std::string>{ "Name","Handle" };
}
