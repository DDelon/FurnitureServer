#include "MessageManager.h"
#include "ThreadManager.h"
#include "ServerManager.h"
#include "EventDispatcher.h"
MessageManager::MessageManager()
{
	ThreadManager::getInstance()->addTask([&](MyThread *pThread) {
		this->loop(pThread);
	});
}

MessageManager::~MessageManager()
{

}

MessageManager *MessageManager::_pInstance = nullptr;
MessageManager *MessageManager::getInstance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new MessageManager();
	}

	return _pInstance;
}

void MessageManager::addReflact(int id, std::string listenerName)
{
	_messageReflact.insert(std::make_pair(id, listenerName));
}

void MessageManager::pushRecvMessage(int socketId, std::string message)
{
	_recvMessageVec.push_back(std::make_pair(socketId, message));
}

void MessageManager::pushSendMessage(int socketId, std::string message)
{
	_sendMessageVec.push_back(std::make_pair(socketId, message));
}

std::string MessageManager::getReflactValue(int id)
{
	return _messageReflact[id];
}

void MessageManager::loop(MyThread *pThread)
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

void MessageManager::dispatcherRecv(std::pair<int, std::string> message)
{
	auto iter = _messageReflact.find(message.first);
	if (iter != _messageReflact.end())
	{
		std::string listenerName = this->getReflactValue(message.first);

		EventDispatcher::getInstance()->dispatcher(listenerName, Value(message.second));
	}
}

void MessageManager::dispatcherSend(std::pair<int, std::string> message)
{
	ServerManager::getInstance()->pushSendMessage(message.first, message.second);
}