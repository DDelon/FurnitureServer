#ifndef __DATEBASE_CONNECT_H__
#define __DATEBASE_CONNECT_H__
#include <iostream>
#include <mysql.h>
#include "CCValue.h"

class DatebaseConnect
{
public:
	DatebaseConnect();
	~DatebaseConnect();

public:
	bool connect(const char *pUser, const char *pPassword, const char *pHost, const char *pDatebase, unsigned int port);

	const char *getErrorStr() { return _errorStr; }

	bool query(char *pQuerySQL);

	::Value getQueryResult();

	void close();
private:
	static int _count;
	int _id;

	MYSQL _mysql;
	MYSQL_RES *_queryResult;
	MYSQL_ROW _singleRecord;
	MYSQL_FIELD *_field;

	const char *_errorStr;
};

#endif