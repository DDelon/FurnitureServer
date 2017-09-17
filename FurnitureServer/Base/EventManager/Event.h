#ifndef __EVENT_H__
#define __EVENT_H__

#include "CCValue.h"

class Event
{
public:
	Event(std::string key, int id, Value val);
	virtual ~Event();

	std::string getKey() { return _key;  }

	int getId() { return _id; }

	Value getValue() { return _val; }

protected:
	std::string _key;
	int _id;

	Value _val;
};

#endif // !__EVENT_H__
