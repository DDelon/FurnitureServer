#include "DatabaseManager.h"
#include "DatabaseConnect.h"
DatabaseManager::DatabaseManager()
{

}

DatabaseManager::~DatabaseManager()
{

}

DatabaseManager *DatabaseManager::_pInstance = nullptr;
DatabaseManager *DatabaseManager::getInstance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new DatabaseManager();
	}

	return _pInstance;
}

void DatabaseManager::createConnect(const char *pUser, const char *pPassword, const char *pHost, const char *pDatebase, unsigned int port)
{
	DatabaseConnect *pConnect = new DatabaseConnect();
	if (pConnect->connect(pUser, pPassword, pHost, pDatebase, port))
	{
		_connectMap.insert(std::make_pair(pDatebase, pConnect));
	}
}

::Value DatabaseManager::query(const char *pDatebase, char *pSQL)
{
	auto iter = _connectMap.find(pDatebase);
	if (iter != _connectMap.end())
	{
		if (iter->second->query(pSQL))
		{
			return iter->second->getQueryResult();
		}
		else
		{
			return Value();
		}
	}
	else
	{
		return Value();
	}
}