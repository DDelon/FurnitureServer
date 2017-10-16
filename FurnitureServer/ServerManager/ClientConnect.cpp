#include "ClientConnect.h"
#include "ServerManager.h"
#include "MessageParser.h"
#include <string>


static std::string key = "wxs123";

ClientConnect::ClientConnect(int socketId) :
Connect::Connect(socketId),
_isRecvHead(true),
_recvContent(""),
_recvTotalLength(0),
_curRecvLength(0),
_recvSign(0),
_sendContent(""),
_isReadable(false),
_isSendable(false),
_isRemove(false)
{
	memset(_szRecvBuffer, '\0', RECV_SIZE);
	memset(_szSendBuffer, '\0', SEND_SIZE);
	int nRecvBuf = 1;
	setsockopt(socketId, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	setsockopt(socketId, SOL_SOCKET, SO_SNDBUF, (const char*)&nRecvBuf, sizeof(int));
}

ClientConnect::~ClientConnect()
{
}

void ClientConnect::initRecvData()
{
	_isRecvHead = true;
	_recvContent = "";
	_recvTotalLength = 0;
	_curRecvLength = 0;
	_recvSign = 0;
	_isReadable = false;
	memset(_szRecvBuffer, '\0', RECV_SIZE);
}

void ClientConnect::initSendData()
{
	_sendContent = "";
	_sendTotalLength = 0;
	_curSendLength = 0;
	_isSendable = false;
	memset(_szSendBuffer, '\0', SEND_SIZE);
}

void ClientConnect::pushSendMessage(std::string message)
{
	this->initSendData();

	_sendContent = message;
	_sendTotalLength = message.size();
	
	this->makePackage(message);

	_isSendable = true;
}

void ClientConnect::makePackage(std::string message)
{
	char sign = this->getSign(message);
	std::string lengthStr = this->encodeLength(message.size());

	for (int i = 0; i < 4; ++i)
	{
		_szSendBuffer[i] = lengthStr[i];
	}
	_szSendBuffer[4] = sign;
	strcpy(&_szSendBuffer[PACKAGE_HEAD_LEN], message.c_str());
	this->encode(_szSendBuffer, message.size()+ PACKAGE_HEAD_LEN, key);
}

void ClientConnect::sendMessage()
{
	
	int size = send(this->_socketId, &_szSendBuffer[_curSendLength], _sendTotalLength+ PACKAGE_HEAD_LEN, 0);
	_curSendLength += size;

	if (_curSendLength >= _sendTotalLength + PACKAGE_HEAD_LEN)
	{
		this->initSendData();
		return;
	}
	
}

void ClientConnect::recvMessage()
{
	char buffer[BUFF_SIZE] = { 0 };
	int size = recv(this->_socketId, buffer, sizeof(buffer), 0);
	if (size > 0)
	{
		memcpy(&_szRecvBuffer[_curRecvLength], buffer, size);
		_curRecvLength += size;
		if (_isRecvHead)
		{
			_recvTotalLength = this->decodeLength(buffer);
			_recvSign = buffer[4];
			_isRecvHead = false;

			std::cout << "id:" << _socketId << " package length:" << _recvTotalLength << " sign:" << (int)_recvSign << std::endl;
		}

		if (_recvTotalLength == (_curRecvLength - PACKAGE_HEAD_LEN))
		{
			//recv complete
			this->decode(_szRecvBuffer, _curRecvLength, key);
			_recvContent.assign(&_szRecvBuffer[PACKAGE_HEAD_LEN]);
			if (this->verifySign(_recvSign, _recvContent))
			{
				//send complete data
				std::cout << "size:" << _recvTotalLength << " message:" << _recvContent << std::endl;
				MessageParser::getInstance()->pushSendMessage(this->_socketId, _recvContent);
			}

			this->initRecvData();
		}
	}
	else
	{
		_isRemove = true;
		//ServerManager::getInstance()->clear(_socketId);
	}
}

std::string ClientConnect::encodeLength(unsigned int length)
{
	std::string sLength = "";
	sLength.assign((char *)&length);

	for (int i = sLength.size(); i < sizeof(unsigned int); ++i)
	{
		sLength += '\0';
	}

	for (int i = 0; i < sLength.size(); ++i)
	{
		sLength[i] ^= 0xff;
	}


	return sLength;
}

unsigned int ClientConnect::decodeLength(char *lengthStr)
{
	char length[4] = { 0 };
	for (int i = 0; i < 4; ++i)
	{
		length[i] = lengthStr[i] ^ 0xff;
	}

	return *((unsigned int *)length);
}

void ClientConnect::encode(char *str, int size, std::string key)
{
	int beginIndex = PACKAGE_HEAD_LEN;
	for (int i = beginIndex; i < size; ++i)
	{
		str[i] ^= key[(i - beginIndex)%key.size()];
	}
}

void ClientConnect::decode(char *str, int size, std::string key)
{
	int beginIndex = PACKAGE_HEAD_LEN;
	for (int i = beginIndex; i < size; ++i)
	{
		str[i] ^= key[(i - beginIndex)%key.size()];
	}
}

char ClientConnect::getSign(std::string &content)
{
	char sign = 0;
	for (int i = 0; i < content.size(); ++i)
	{
		sign ^= content[i];
	}

	return sign;
}

bool ClientConnect::verifySign(char sign, std::string content)
{
	char nowSign = 0;
	for (int i = 0; i < content.size(); ++i)
	{
		nowSign ^= content[i];
	}
	return (sign == nowSign);
}