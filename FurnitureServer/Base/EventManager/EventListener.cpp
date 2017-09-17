#include "EventListener.h"

int EventListener::_count = 0;

EventListener::EventListener(std::string key, std::function<void(std::string, int, Value)> func) :
_key(key),
_id(EventListener::_count++),
_func(func)
{
}

EventListener::~EventListener()
{
}

void EventListener::response(Value val)
{
	_func(_key, _id, val);
}