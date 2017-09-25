#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__
#include "CCValue.h"
class FileUtils
{
public:
	FileUtils();
	~FileUtils();

public:
	static FileUtils *getInstance();

	::Value getValueMapFromXML(const std::string fileName);

private:
	static FileUtils *_pInstance;
};

#endif