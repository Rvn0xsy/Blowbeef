#include "DNS_Cache.h"

DNS_Cache::DNS_Cache()
{
    this->SetModuleName("DNS_Cache");
	this->SetWMIDescription("DNSCache");
	this->SetWMINameSpace("Root\\StandardCimv2");
	this->SetWMIQuery("select Data,Name from MSFT_DNSClientCache");
	this->moduleWMIKey = std::vector<std::string>{ "Data","Name" };
}
