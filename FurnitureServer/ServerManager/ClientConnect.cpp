#include "ClientConnect.h"
#include "ServerManager.h"
#define BUFF_SIZE 1024

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
_isSendable(false)

{

}

ClientConnect::~ClientConnect()
{
}

void ClientConnect::initData()
{
	_isRecvHead = true;
	_recvContent = "";
	_recvTotalLength = 0;
	_curRecvLength = 0;
	_recvSign = 0;
	_isReadable = false;
}

void ClientConnect::pushSendMessage(std::string message)
{
	_sendContent = message;
	this->encode(_sendContent, key);
	this->addLength(_sendContent, _sendContent.size());
	_isSendable = true;
}

void ClientConnect::sendMessage()
{
	if (_sendContent.size() == 0)
	{
		_isSendable = false;
		return;
	}

	int size = send(this->_socketId, _sendContent.c_str(), _sendContent.size(), 0);
	_sendContent.erase(0, size);
	
}

void ClientConnect::recvMessage()
{
	char buffer[BUFF_SIZE] = { 0 };
	int size = recv(this->_socketId, buffer, sizeof(buffer), 0);
	if (size > 0)
	{
		_curRecvLength += size;
		_recvContent += buffer;
		if (_isRecvHead)
		{
			_recvTotalLength = this->getLength(_recvContent);
			_recvSign = this->getSign(_recvContent);
			_isRecvHead = false;

			if (_recvTotalLength <= _curRecvLength)
			{
				//recv complete
				_recvContent += '\0';
				if (this->verifySign(_recvSign, _recvContent))
				{
					this->decode(_recvContent, key);

					//send complete data

				}

				this->initData();
			}
		}
		else
		{
			if (_recvTotalLength <= _curRecvLength)
			{
				//recv complete
				_recvContent += '\0';
				if (this->verifySign(_recvSign, _recvContent))
				{
					this->decode(_recvContent, key);

					//send complete data

				}
				
				this->initData();
			}
		}
	}
	else
	{
		ServerManager::getInstance()->clear(_socketId);
	}
}

void ClientConnect::addLength(std::string &content, unsigned int length)
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

	this->addSign(content);

	content = sLength + content;
}

int ClientConnect::getLength(std::string &content)
{
	std::string sLength = content.substr(0, 4);
	content.erase(0, 4);

	for (int i = 0; i < sLength.size(); ++i)
	{
		sLength[i] ^= 0xff;
	}

	return *((unsigned int *)sLength.c_str());
}

void ClientConnect::encode(std::string &str, std::string key)
{
	for (int i = 0; i < str.size(); ++i)
	{
		str[i] ^= key[i%key.size()];
	}
}

void ClientConnect::decode(std::string &str, std::string key)
{
	for (int i = 0; i < str.size(); ++i)
	{
		str[i] ^= key[i%key.size()];
	}
}

void ClientConnect::addSign(std::string &content)
{
	char sign = 0;
	for (int i = 0; i < content.size(); ++i)
	{
		sign ^= content[i];
	}

	content = sign + content;
}

char ClientConnect::getSign(std::string &content)
{
	char sign = *(content.substr(0, 1).c_str());
	content.erase(0, 1);

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