#include "Event.h"

Event::Event(std::string key, int id, Value val) :
_key(key),
_id(id),
_val(val)
{
}

Event::~Event()
{
}