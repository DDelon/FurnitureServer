#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__



#include <iostream>
#include <WinSock2.h>
#include <map>

class ListenerConnect;

class ClientConnect;

class MyThread;

class ServerManager
{
private:
	ServerManager();
	~ServerManager();

public:
	static ServerManager *getInstance();

	void start();

	void stop();

	void pushSendMessage(int socketId, std::string message);

	void clear(int socketId);

	void joinClient(int socketId);

private:
	void createListenerSocket();

	timeval createTimeout();

	void mainLoop();

	void recvMessageLoop(MyThread *pThread);

	void sendMessageLoop(MyThread *pThread);

private:
	static ServerManager *_pInstance;

	fd_set _fdSockets;

	ListenerConnect *_pListener;

	std::map<int, ClientConnect *> _connectSet;
};

#endif // !__SERVER_MANAGER_H__
