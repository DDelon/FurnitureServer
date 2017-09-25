#include "FileManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

FileManager *FileManager::_pInstance = nullptr;
FileManager *FileManager::getInstance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new FileManager();
	}

	return _pInstance;
}

::Value FileManager::getValueFromTxt(const std::string fileName)
{
	std::string content;
	std::ifstream io;
	io.open(fileName.c_str());
	io >> content;

	rapidjson::Document doc;
	doc.Parse<0>(content.c_str());
	rapidjson::Value &node = doc["ListenerPort"];
	std::cout << "listener port:" << node.GetString() << std::endl;

}

::Value FileManager::getConfigFromTxt(const std::string fileName, const std::string dbname)
{
	::ValueMap config;
	std::string content;
	std::ifstream io;
	io.open(fileName.c_str());
	while (!io.eof())
	{
		char temp;
		io >> temp;
		content += temp;
	}

	rapidjson::Document doc;
	doc.Parse<0>(content.c_str());
	rapidjson::Value &node1 = doc["ListenerPort"];
	std::cout << "listener port:" << node1.GetType() << std::endl;
	config["ListenerPort"] = Value(node1.GetString());

	rapidjson::Value &node2 = doc["logindb"];
	if (node2.IsObject())
	{
		::ValueMap dbConfig;
		for (auto iter = node2.Begin(); iter != node2.End(); ++iter)
		{
			std::cout << "awdwdwa" << std::endl;
		}
	}
}

