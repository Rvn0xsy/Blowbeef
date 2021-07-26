#include "DISK_Volume.h"

DISK_Volume::DISK_Volume()
{
	this->SetModuleName("DISK_Volume");
	this->SetWMIDescription("VolumeState");
	this->SetWMINameSpace("root\\cimv2");
	this->SetWMIQuery("select Name,BootVolume,Label from Win32_Volume");
	this->moduleWMIKey = std::vector<std::string>{ "Name","BootVolume","Label"};
}