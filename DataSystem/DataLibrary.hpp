/*!
 * \class DataLibrary
 *
 * \brief 
 *
 * \author 李翔;
 * \date 十二月 2014;
 */

/*
使用方法 :

定义实例
DataLibrary dataLibrary;
给定要读取的文件路径(这里注意 这里是读取Csv文件, 并且文件的第一行必须为 id$int, name$string, sex$string, tall$float  这种格式的,并且第一列必须为自增 id)
dataLibrary.LoadDataFromResource("文件路径"); 
获取数据(获取数据有多种方法请看源文件)
dataLibrary[1][name].ToString()*/

#pragma once


#include "../CsvParser/CsvReader.h"
#include "../StringUtil/StringUtil.h"
#include <boost/foreach.hpp>
#include "BasicData.h"


class DataLibrary : public CSVReader
{
 
public:

	DataLibrary()
	{

	}

	virtual ~DataLibrary()
	{
		ClearLibrary();
	}

	virtual const BasicData& GetDataByKey(int aId) const
	{
		std::map<int, BasicData*>::const_iterator itr = _mapLibrary.find(aId);
		assert(itr != _mapLibrary.end());
		return *(itr->second);
	}

	virtual const std::map<int, BasicData*>& getAllData() const
	{
		return _mapLibrary;
	}

	virtual const BasicData* GetDataPointerByKey(int aId) const
	{
		std::map<int, BasicData*>::const_iterator itr = _mapLibrary.find(aId);
		assert(itr != _mapLibrary.end());
		return itr->second;
	}

	int GetDataRecordCount() const
	{
		return _mapLibrary.size();
	}

	virtual bool LoadDataFromResource(const std::string &aSource, int skip_line = 0) override
	{
		if (_mapLibrary.size() != 0)
		{
			ClearLibrary();
		}

		//注意:这是就是最牛B 的函数;
		return CSVReader::LoadDataFromResource(aSource);
	}

	virtual BasicData& operator[](const int& aId)
	{
		std::map<int, BasicData*>::const_iterator itr = _mapLibrary.find(aId);
		assert(itr != _mapLibrary.end());
		return *(itr->second);
	}

protected:

	virtual void ParseHead(const std::vector<std::string>& aRowData)
	{
		BOOST_FOREACH(string field, aRowData)
		{
			std::vector<std::string> split = StringUtil::Split(field, "$");
			assert(split.size() > 1);
			_vecHead.push_back(std::make_pair(split[0], split[1]));
		}
	}

	virtual void ParseData(const std::vector<std::string> &aRowData)
	{
		assert(aRowData.size() == _vecHead.size());

		BasicData *pData = new BasicData();
		for (unsigned int i = 0; i < aRowData.size(); ++i)
		{
			pData->ParseData(
				_vecHead[i].first,		// key
				_vecHead[i].second,	// type
				aRowData[i]);			// value
		}

		_mapLibrary[GetDataKey(pData)] = pData;
	}

	virtual void ParseLine(unsigned int aIndex, const std::vector<std::string> &aRow) override
	{
		if (aIndex == 0)
		{
			ParseHead(aRow);
		}
		else
		{
			ParseData(aRow);
		}
	}

	virtual int GetDataKey(BasicData *aData) const
	{
		int key;
		//注意这里是唯一死板的地方,如果CSV文件有改动,这里就必须改.文件第一个字段必须为 "id";
		(*aData)["id"] >> key;
		return key;
	}

	void ClearLibrary()
	{
		BOOST_FOREACH(auto mapElem, _mapLibrary)
		{
			if (mapElem.second)
			{
				delete mapElem.second;
			}
		}

		_mapLibrary.clear();
		_vecHead.clear();
	}

protected:

	std::vector<BasicData::DataHead> _vecHead;
	std::map<int, BasicData*> _mapLibrary;
};