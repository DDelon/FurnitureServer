#ifndef __MESSAGE_PARSER_H__
#define __MESSAGE_PARSER_H__
#include "MessageConstant.h"
#include <iostream>
#include <vector>
#include <map>

class MyThread;

class MessageParser
{
private:
	MessageParser();
	~MessageParser();

public:
	static MessageParser *getInstance();

	void addReflact(int id, std::string listenerName);

	void pushRecvMessage(int socketId, std::string message);

	void pushSendMessage(int socketId, std::string message);

	std::string getReflactValue(int id);

private:
	void loop(MyThread *pThread);

	void dispatcherRecv(std::pair<int, std::string> message);

	void dispatcherSend(std::pair<int, std::string> message);

private:
	static MessageParser *_pInstance;

	std::map<int, std::string> _messageReflact;

	std::vector<std::pair<int, std::string>> _recvMessageVec;
	std::vector<std::pair<int, std::string>> _sendMessageVec;
};

#endif