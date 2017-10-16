#include "GameManager.h"
#include "MessageParser.h"
GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

GameManager *GameManager::_pInstance = nullptr;
GameManager *GameManager::getInstance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new GameManager();
	}

	return _pInstance;
}

void GameManager::registerParser()
{
	MessageParser::getInstance()->addReflact(MSGLoginC2S, "MSGLoginC2S");
	MessageParser::getInstance()->addReflact(MSGLoginS2C, "MSGLoginS2C");
}
