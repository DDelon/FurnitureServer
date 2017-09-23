#ifndef __DATEBASE_MANAGER_H__
#define __DATEBASE_MANAGER_H__
#include "CCValue.h"
#include <map>

class DatebaseConnect;

class DatebaseManager
{
private:
	DatebaseManager();
	~DatebaseManager();
public:
	static DatebaseManager *getInstance();

	void createConnect(const char *pUser, const char *pPassword, const char *pHost, const char *pDatebase, unsigned int port);

	::Value query(const char *pDatebase, char *pSQL);

private:
	static DatebaseManager *_pInstance;

	std::map<std::string, DatebaseConnect *> _connectMap;

	
};

#endif