#ifndef __CLIENT_CONNECT_H__
#define __CLIENT_CONNECT_H__
#include "Connect.h"

#define RECV_SIZE 5000
#define SEND_SIZE 5000
#define BUFF_SIZE 1024
#define PACKAGE_HEAD_LEN 5

class ClientConnect : public Connect
{
public:
	ClientConnect(int socketId);
	~ClientConnect();

public:
	void pushSendMessage(std::string message);

	void sendMessage();

	void recvMessage();

	void setReadable(bool isReadable) { _isReadable = isReadable; }

	bool isReadable() { return _isReadable; }

	void setSendable(bool isSendable) { _isSendable = isSendable; }

	bool isSendable() { return _isSendable; }

	bool isRemove() { return _isRemove; }

protected:
	void initRecvData();

	void initSendData();

	void makePackage(std::string message);

	std::string encodeLength(unsigned int length);

	unsigned int decodeLength(char *lengthStr);

	void encode(char *str, int size, std::string key);
	
	void decode(char *str, int size, std::string key);

	char getSign(std::string &content);

	bool verifySign(char sign, std::string content);

private:

	bool _isRecvHead;
	std::string _recvContent;
	int _recvTotalLength;
	int _curRecvLength;
	char _recvSign;

	std::string _sendContent;

	bool _isReadable;
	bool _isSendable;
	bool _isRemove;

	int _sendTotalLength;
	int _curSendLength;

	char _szRecvBuffer[RECV_SIZE];
	char _szSendBuffer[RECV_SIZE];
};

#endif