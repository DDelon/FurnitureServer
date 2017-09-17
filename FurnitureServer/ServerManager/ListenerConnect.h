#ifndef __LISTENER_CONNECT_H__
#define __LISTENER_CONNECT_H__
#include "Connect.h"

class ListenerConnect : public Connect
{
public:
	ListenerConnect(int socketId);
	~ListenerConnect();

public:
	bool joinNewClient(int setNum);
};

#endif // !__LISTENER_CONNECT_H__
