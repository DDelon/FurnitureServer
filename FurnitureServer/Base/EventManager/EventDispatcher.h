#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include "CCValue.h"

class EventListener;
class Event;

class EventDispatcher
{
public:
	typedef std::vector<EventListener *> listenerVec;

public:
	static EventDispatcher *getInstance();

	int registerListener(std::string key, std::function<void(std::string, int, Value)> func);
	void registerListener(EventListener *pListener);


	void dispatcher(std::string key, Value val);
	void dispatcher(std::string key, int id, Value val);
	void dispatcher(Event *pEvent);


	void removeListener(std::string key);
	void removeListener(std::string key, int id);

private:
	EventDispatcher();
	~EventDispatcher();

private:
	static EventDispatcher *_pInstance;

	std::map<std::string, listenerVec> _listenerContainer;
};

#endif // !__EVENT_MANAGER_H__



