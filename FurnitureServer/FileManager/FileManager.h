#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__
#include "CCValue.h"
class FileManager
{
public:
	FileManager();
	~FileManager();

public:
	static FileManager *getInstance();

	::Value getValueFromTxt(const std::string fileName);

	::Value getConfigFromTxt(const std::string fileName, const std::string dbname);

private:
	static FileManager *_pInstance;
};

#endif