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

const DataUnit* BasicData::GetField(const std::string& aKey) const
{
	std::string lowerKey = StringUtil::ToLowercaseRet(aKey);
	std::map<std::string, DataUnit>::const_iterator itr = _mapData.find(lowerKey);
	assert(itr != _mapData.end());
	return &(itr->second);
}

void BasicData::ParseData(const std::string &aKey, const std::string &aType, const std::string &aVal)
{
	std::string key = StringUtil::ToLowercaseRet(aKey);

	if (aType == "char")
	{
		_mapData[aKey] << (char)atoi(aVal.c_str());
	}
	else if (aType == "short")
	{
		_mapData[aKey] << (short)atoi(aVal.c_str());
	}
	else if (aType == "int")
	{
		_mapData[key] << atoi(aVal.c_str());
	}
	else if (aType == "float")
	{
		_mapData[key] << (float)atof(aVal.c_str());
	}
	else if (aType == "double")
	{
		_mapData[key] << (double)atof(aVal.c_str());
	}
	else if (aType == "long")
	{
		_mapData[key] << atol(aVal.c_str());
	}
	else if (aType == "long long")
	{
		_mapData[key] << StringUtil::Atoll(aVal);
	}
	else if (aType == "string")
	{
		_mapData[key] << aVal.c_str();
	}
	else 
	{
		assert(false);
	}
}
