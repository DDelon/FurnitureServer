#include "ListenerConnect.h"
#include "ClientConnect.h"
#include "ServerManager.h"

ListenerConnect::ListenerConnect(int socketId) :
Connect::Connect(socketId)
{

}

ListenerConnect::~ListenerConnect()
{

}

bool ListenerConnect::joinNewClient(int setNum)
{
	if (setNum < FD_SETSIZE)
	{
		sockaddr_in addrRemote = { 0 };
		int addrLen = sizeof(addrRemote);
		int socketNew = accept(this->_socketId, (sockaddr *)&addrRemote, &addrLen);
		std::cout << "new client join id:" << socketNew << " ip:" << inet_ntoa(addrRemote.sin_addr) << " port:" << ntohs(addrRemote.sin_port) << std::endl;
		ServerManager::getInstance()->joinClient(socketNew);
		return true;
	}
	else
	{
		std::cout << "too many connection error" << std::endl;
		return false;
	}
}