#include "IPAddress.h"

IPAddress::IPAddress()
{
	this->SetModuleName("Net_IPAddress");
	this->SetWMIDescription("IPAddress");
	this->SetWMINameSpace("Root\\StandardCimv2");
	this->SetWMIQuery("select InterfaceAlias,IPAddress from MSFT_NetIPAddress");
	this->moduleWMIKey = std::vector<std::string>{ "InterfaceAlias","IPAddress" };
}
