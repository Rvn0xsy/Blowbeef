#include "NetRoute.h"


NetRoute::NetRoute()
{
	this->SetModuleName("Net_Route");
	this->SetWMIDescription("NetRoute");
	this->SetWMINameSpace("Root\\StandardCimv2");
	this->SetWMIQuery("select DestinationPrefix,InterfaceAlias from MSFT_NetRoute");
	this->moduleWMIKey = std::vector<std::string>{ "DestinationPrefix","InterfaceAlias" };
}
