#include "DatebaseConnect.h"
DatebaseConnect::DatebaseConnect()
{
	_id = _count++;
	mysql_init(&_mysql);
}

DatebaseConnect::~DatebaseConnect()
{
	this->close();
}


int DatebaseConnect::_count = 0;
bool DatebaseConnect::connect(const char *pUser, const char *pPassword, const char *pHost, const char *pDatebase, unsigned int port)
{
	if (mysql_real_connect(&_mysql, pHost, pUser, pPassword, pDatebase, port, NULL, 0))
	{
		mysql_query(&_mysql, "SET NAMES GBK");
		return true;
	}
	else
	{
		_errorStr = mysql_error(&_mysql);
		return false;
	}
}

bool DatebaseConnect::query(char *pQuerySQL)
{
	int res = mysql_query(&_mysql, pQuerySQL);
	return !res;
}

::Value DatebaseConnect::getQueryResult()
{
	_queryResult = mysql_store_result(&_mysql);
	if (_queryResult)
	{
		ValueVector val;
		std::vector<std::string> keys;
		std::cout << "query result number:" << (unsigned long)mysql_num_rows(_queryResult) << std::endl;
		for (int i = 0; _field = mysql_fetch_field(_queryResult); ++i)
		{
			std::string key = _field->name;
			keys.push_back(key);
		}
		while (_singleRecord = mysql_fetch_row(_queryResult))
		{
			ValueMap map;
			int i = 0;
			for (auto iter : keys)
			{
				map.insert(std::make_pair(iter, Value(_singleRecord[i++])));
			}
			val.push_back(Value(map));
		}

		if (_queryResult != nullptr)
		{
			mysql_free_result(_queryResult);
		}

		return Value(val);
	}
	else
	{
		return Value();
	}
}

void DatebaseConnect::close()
{
	mysql_close(&_mysql);
}