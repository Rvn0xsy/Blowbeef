#include "NetRoute.h"


NetRoute::NetRoute()
{
	this->SetModuleName("Net_IPAddress");
	this->SetWMIDescription("NetRoute");
	this->SetWMINameSpace("Root\\StandardCimv2");
	this->SetWMIQuery("select DestinationPrefix,IPAddress from MSFT_NetRoute");
	this->moduleWMIKey = std::vector<std::string>{ "DestinationPrefix","IPAddress" };
}
