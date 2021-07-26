#include "NetTCPConnection.h"


NetTCPConnection::NetTCPConnection()
{
	this->SetModuleName("Net_TCPConnection");
	this->SetWMIDescription("TCPConnection");
	this->SetWMINameSpace("Root\\StandardCimv2");
	this->SetWMIQuery("select LocalAddress,LocalPort,RemoteAddress,RemotePort,OwningProcess from MSFT_NetTCPConnection");
	this->moduleWMIKey = std::vector<std::string>{"LocalAddress","LocalPort","RemoteAddress","RemotePort","OwningProcess" };
}
