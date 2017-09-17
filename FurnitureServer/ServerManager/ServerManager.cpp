#include "ServerManager.h"
#include "ClientConnect.h"
#include "ListenerConnect.h"
#include "ThreadManager.h"
#define PORT 55221


ServerManager::ServerManager() :
_pListener(nullptr)
{
	std::cout << "1" << std::endl;
}

ServerManager::~ServerManager()
{
}

ServerManager *ServerManager::_pInstance = nullptr;
ServerManager *ServerManager::getInstance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new ServerManager();
	}

	return _pInstance;
}

void ServerManager::start()
{
	this->createListenerSocket();

	ThreadManager::getInstance()->addTask([&](MyThread *pThread) {
		this->recvMessageLoop(pThread);
	});

	ThreadManager::getInstance()->addTask([&](MyThread *pThread) {
		this->sendMessageLoop(pThread);
	});

	this->mainLoop();
	
}

void ServerManager::stop()
{
}

void ServerManager::pushSendMessage(int socketId, std::string message)
{
	_connectSet[socketId]->pushSendMessage(message);
}

void ServerManager::clear(int socketId)
{
	closesocket(socketId);
	FD_CLR(socketId, &_fdSockets);

	auto iter = _connectSet.find(socketId);
	if (iter != _connectSet.end())
	{
		_connectSet.erase(iter);
		delete iter->second;
	}
}

void ServerManager::joinClient(int socketId)
{
	FD_SET(socketId, &_fdSockets);

	ClientConnect *pConnect = new ClientConnect(socketId);
	_connectSet.insert(std::make_pair(socketId, pConnect));
}

void ServerManager::createListenerSocket()
{

	WSADATA     wsaData;
	WORD wVersionRequested = MAKEWORD(2, 0);
	int32_t nRet = WSAStartup(wVersionRequested, &wsaData);
	if (nRet != S_OK)
	{
		std::cout << "wsadata init fail" << std::endl;
	}

	int listenerId = socket(AF_INET, SOCK_STREAM, 0);
	int errorCode = WSAGetLastError();
	if (listenerId == INVALID_SOCKET)
	{
		std::cout << "invalid socket error code:" << errorCode << std::endl;
		return;
	}

	//bind listener port
	sockaddr_in serverAddr = { 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = ::htons(PORT);
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (SOCKET_ERROR == bind(listenerId, (sockaddr *)&serverAddr, sizeof(sockaddr)))
	{
		std::cout << "connect error" << std::endl;
	}

	//join listener socket to fd set
	listen(listenerId, 5);
	FD_ZERO(&_fdSockets);
	FD_SET(listenerId, &_fdSockets);

	_pListener = new ListenerConnect(listenerId);
}

timeval ServerManager::createTimeout()
{
	timeval timeout;
	timeout.tv_sec = 500;
	timeout.tv_usec = 0;
	return timeout;
}

void ServerManager::mainLoop()
{

	while (true)
	{
		fd_set fdBackup = _fdSockets;
		int ret = select(0, &fdBackup, NULL, NULL, &this->createTimeout());
		std::cout << "main loop" << std::endl;
		if (ret > 0)
		{
			for (int i = 0; i < _fdSockets.fd_count; ++i)
			{
				if (FD_ISSET(_fdSockets.fd_array[i], &fdBackup))
				{
					if (_fdSockets.fd_array[i] == _pListener->getSocketId())
					{
						if (!_pListener->joinNewClient(_fdSockets.fd_count))
							continue;
					}
					else
					{
						std::cout << "read event" << std::endl;
						_connectSet[_fdSockets.fd_array[i]]->setReadable(true);
					}
				}
			}
		}
		else
		{
			std::cout << "select ret 0" << std::endl;
			return;
		}
	}

	closesocket(_pListener->getSocketId());
	delete _pListener;
}

void ServerManager::recvMessageLoop(MyThread *pThread)
{
	if (pThread->lock())
	{

		for (auto iter : _connectSet)
		{
			if (iter.second->isReadable())
			{
				iter.second->recvMessage();
			}
		}

		pThread->unlock();
	}

}

void ServerManager::sendMessageLoop(MyThread *pThread)
{
	if (pThread->lock())
	{
		for (auto iter : _connectSet)
		{
			if (iter.second->isSendable())
			{
				iter.second->sendMessage();
			}
		}

		pThread->unlock();
	}
}
