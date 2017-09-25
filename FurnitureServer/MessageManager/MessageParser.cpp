#include "MessageParser.h"
#include "ThreadManager.h"
#include "ServerManager.h"
#include "EventDispatcher.h"
MessageParser::MessageParser()
{
	ThreadManager::getInstance()->addTask([&](MyThread *pThread) {
		this->loop(pThread);
	});
}

MessageParser::~MessageParser()
{

}

MessageParser *MessageParser::_pInstance = nullptr;
MessageParser *MessageParser::getInstance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new MessageParser();
	}

	return _pInstance;
}

void MessageParser::addReflact(int id, std::string listenerName)
{
	_messageReflact.insert(std::make_pair(id, listenerName));
}

void MessageParser::pushRecvMessage(int socketId, std::string message)
{
	_recvMessageVec.push_back(std::make_pair(socketId, message));
}

void MessageParser::pushSendMessage(int socketId, std::string message)
{
	_sendMessageVec.push_back(std::make_pair(socketId, message));
}

std::string MessageParser::getReflactValue(int id)
{
	return _messageReflact[id];
}

void MessageParser::loop(MyThread *pThread)
{
	if (pThread->lock())
	{
		
		for (auto iter = _recvMessageVec.begin(); iter != _recvMessageVec.end(); ++iter)
		{
			this->dispatcherRecv(*iter);
			_recvMessageVec.erase(iter);
			break;
		}

		for (auto iter = _sendMessageVec.begin(); iter != _sendMessageVec.end(); ++iter)
		{
			this->dispatcherSend(*iter);
			_sendMessageVec.erase(iter);
			break;
		}


		pThread->unlock();
	}
}

void MessageParser::dispatcherRecv(std::pair<int, std::string> message)
{
	auto iter = _messageReflact.find(message.first);
	if (iter != _messageReflact.end())
	{
		std::string listenerName = this->getReflactValue(message.first);
		EventDispatcher::getInstance()->dispatcher(listenerName, Value(message.second));
	}
}

void MessageParser::dispatcherSend(std::pair<int, std::string> message)
{
	ServerManager::getInstance()->pushSendMessage(message.first, message.second);
}