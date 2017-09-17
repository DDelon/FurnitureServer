#include "EventDispatcher.h"
#include "EventListener.h"
#include "Event.h"

EventDispatcher::EventDispatcher()
{
}


EventDispatcher::~EventDispatcher()
{
}

EventDispatcher *EventDispatcher::_pInstance = nullptr;
EventDispatcher *EventDispatcher::getInstance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new EventDispatcher();
	}

	return _pInstance;
}

int EventDispatcher::registerListener(std::string key, std::function<void(std::string, int, Value)> func)
{
	EventListener *pListener = new EventListener(key, func);

	this->registerListener(pListener);

	return pListener->getId();
}

void EventDispatcher::registerListener(EventListener *pListener)
{
	
	auto iter = _listenerContainer.find(pListener->getKey());
	if (iter != _listenerContainer.end())
	{
		(*iter).second.push_back(pListener);
	}
	else
	{
		listenerVec tempVec;
		tempVec.push_back(pListener);
		_listenerContainer.insert(std::make_pair(pListener->getKey(), tempVec));
	}
}

void EventDispatcher::dispatcher(std::string key, Value val)
{
	auto iter = _listenerContainer.find(key);
	if (iter != _listenerContainer.end())
	{
		for (auto listener : (*iter).second)
		{
			listener->response(val);
		}
	}
}

void EventDispatcher::dispatcher(std::string key, int id, Value val)
{
	auto iter = _listenerContainer.find(key);
	if (iter != _listenerContainer.end())
	{
		for (auto listener : (*iter).second)
		{
			if (listener->getId() == id)
			{
				listener->response(val);
			}
		}
	}
}

void EventDispatcher::dispatcher(Event *pEvent)
{
	this->dispatcher(pEvent->getKey(), pEvent->getId(), pEvent->getValue());
}

void EventDispatcher::removeListener(std::string key)
{
	auto iter = _listenerContainer.find(key);
	if (iter != _listenerContainer.end())
	{
		for (auto listener = (*iter).second.begin(); listener != (*iter).second.begin(); )
		{
			listener = (*iter).second.erase(listener);
		}

		_listenerContainer.erase(iter);
	}


}

void EventDispatcher::removeListener(std::string key, int id)
{

	auto iter = _listenerContainer.find(key);
	if (iter != _listenerContainer.end())
	{
		for (auto listener = (*iter).second.begin(); listener != (*iter).second.begin(); )
		{
			if ((*listener)->getId() == id)
			{
				listener = (*iter).second.erase(listener);
				break;
			}
			
		}

	}
}
