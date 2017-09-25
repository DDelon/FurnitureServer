#include "FileUtils.h"
#include <fstream>
#include <string>
#include <iostream>
#include "tinyxml.h"
FileUtils::FileUtils()
{

}

FileUtils::~FileUtils()
{

}

FileUtils *FileUtils::_pInstance = nullptr;
FileUtils *FileUtils::getInstance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new FileUtils();
	}

	return _pInstance;
}

::Value FileUtils::getValueMapFromXML(const std::string fileName)
{
	TiXmlDocument *pDoc = new TiXmlDocument();
	bool isLoad = pDoc->LoadFile(fileName.c_str());
	//pDoc->Print();
	TiXmlElement *root = pDoc->FirstChildElement();
	if (root == nullptr)
	{
		std::cout << "Failed to load file: No root element" << std::endl;
		pDoc->Clear();
		return Value();
	}

	for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement())
	{
		std::string name = elem->Value();
	}
	
}

