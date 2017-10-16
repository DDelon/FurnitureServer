#ifndef __DATABASE_MANAGER_H__
#define __DATABASE_MANAGER_H__
#include "CCValue.h"
#include <map>

class DatabaseConnect;

class DatabaseManager
{
private:
	DatabaseManager();
	~DatabaseManager();
public:
	static DatabaseManager *getInstance();

	void createConnect(const char *pUser, const char *pPassword, const char *pHost, const char *pDatebase, unsigned int port);

	::Value query(const char *pDatebase, char *pSQL);

private:
	static DatabaseManager *_pInstance;

	std::map<std::string, DatabaseConnect *> _connectMap;

	
};

#endif