#include "BasicData.h"

#include "StringUtil/StringUtil.h"

BasicData::BasicData()
{

}

BasicData::~BasicData()
{

}

const DataUnit& BasicData::operator[](const std::string& aKey) const
{
	std::string lowerKey = StringUtil::ToLowercaseRet(aKey);
	std::map<std::string, DataUnit>::const_iterator itr = _mapData.find(lowerKey);
	assert(itr != _mapData.end());
	return itr->second;
}

const DataUnit* BasicData::getField(const std::string& aKey) const
{
	std::string lowerKey = StringUtil::ToLowercaseRet(aKey);
	std::map<std::string, DataUnit>::const_iterator itr = _mapData.find(lowerKey);
	assert(itr != _mapData.end());
	return &(itr->second);
}

void BasicData::parseData(
	const std::string &aKey,
	const std::string &aType, 
	const std::string &aValue)
{
	std::string key = StringUtil::ToLowercase(aKey);

	if (aType == "string")
	{
		_mapData[key] << aValue.c_str();
	}
	else if (aType == "int")
	{
		_mapData[key] << atoi(aValue.c_str());
	}
	else if (aType == "float")
	{
		_mapData[key] << (float)atof(aValue.c_str());
	}
}
