#ifndef __EVENT_LISTENER_H__
#define __EVENT_LISTENER_H__
#include <iostream>
#include <functional>
#include "CCValue.h"


class EventListener
{
public:
	EventListener(std::string key, std::function<void (std::string, int, Value)> func);
	virtual ~EventListener();

	int getId() { return _id; }

	std::string getKey() { return _key; }

	void response(Value val);

protected:
	static int _count;

	std::string _key;

	int _id;

	std::function<void(std::string, int, Value)> _func;
};

#endif // !__EVENT_LISTENER_H__
