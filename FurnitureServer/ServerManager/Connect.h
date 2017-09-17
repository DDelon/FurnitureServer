#ifndef __CONNECT_H__
#define __CONNECT_H__
#include <WinSock2.h>
#include <iostream>
class Connect
{
public:
	Connect(int socketId);
	virtual ~Connect();

public:
	int getSocketId() { return _socketId; }

protected:
	int _socketId;
};

#endif // !__CONNECT_H__
