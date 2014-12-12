/********************************************************************
	created:	2014/12/11
	created:	11:12:2014   9:43

	author:		����
	
	purpose:	�����ļ���ȡ��,һЩ�򵥵����е����þ���������ȡ�洢(��:������IP����);
	�����ļ�д��:(ע����CSV�ļ�);
	name$string,	server
	ip$string,			192.168.1.168
	port$int,			8010 
*********************************************************************/


#pragma once

#include "CsvParser/CsvReader.h"

#include "BasicData.h"
#include "StringUtil/StringUtil.h"

class ConfigLibrary : public CSVReader
{
public:

	ConfigLibrary()
	{

	}
	virtual ~ConfigLibrary()
	{

	}

	const DataUnit& operator [] (const std::string& aKey) const
	{
		return _data[aKey];
	}
	const DataUnit& getConfig(const std::string aKey) const
	{
		return _data[aKey];
	}

protected:
	virtual void ParseLine(unsigned int aIndex, const std::vector<std::string>& aRow) override
	{
		assert(aRow.size() == 2);
		std::string head = aRow[0];
		std::vector<std::string> splitedHead = StringUtil::Split(head, "$");
		assert(splitedHead.size() == 2);
		std::string key = splitedHead[0];
		std::string type = splitedHead[1];

		std::string val = aRow[1];

		_data.ParseData(key, type, val);
	}

	BasicData _data;
};
