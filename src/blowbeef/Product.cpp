#include "Product.h"

Product::Product()
{
	this->SetModuleName("Win32Product");
	this->SetWMIDescription("Product");
	this->SetWMINameSpace("ROOT\\CIMV2");
	this->SetWMIQuery("select Name,InstallSource from Win32_Product");
	this->moduleWMIKey = std::vector<std::string>{ "Name","InstallSource" };

}

