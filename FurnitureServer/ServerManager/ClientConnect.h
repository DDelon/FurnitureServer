#ifndef __CLIENT_CONNECT_H__
#define __CLIENT_CONNECT_H__
#include "Connect.h"

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

protected:
	void initData();

	void addLength(std::string &content, unsigned int length);

	int getLength(std::string &content);

	void encode(std::string &str, std::string key);

	void decode(std::string &str, std::string key);

	void addSign(std::string &content);

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
};

#endif