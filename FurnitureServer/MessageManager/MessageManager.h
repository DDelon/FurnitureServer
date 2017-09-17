#ifndef __MESSAGE_MANAGER_H__
#define __MESSAGE_MANAGER_H__

#include <iostream>
#include <vector>
#include <map>

class MyThread;

class MessageManager
{
private:
	MessageManager();
	~MessageManager();

public:
	static MessageManager *getInstance();

	void addReflact(int id, std::string listenerName);

	void pushRecvMessage(int socketId, std::string message);

	void pushSendMessage(int socketId, std::string message);

	std::string getReflactValue(int id);

private:
	void loop(MyThread *pThread);

	void dispatcherRecv(std::pair<int, std::string> message);

	void dispatcherSend(std::pair<int, std::string> message);

private:
	static MessageManager *_pInstance;

	std::map<int, std::string> _messageReflact;

	std::vector<std::pair<int, std::string>> _recvMessageVec;
	std::vector<std::pair<int, std::string>> _sendMessageVec;
};

#endif