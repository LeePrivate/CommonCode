/********************************************************************
	created:	2014/12/09
	created:	9:12:2014   14:25
	author:		李翔;
	
	purpose:	DataSystem 数据基础;
	注意 : 从这里开始引入一个新的命名规则函数参数前面加 a 代表 argument 参数的意思;
	DataUnit 类为数据基类,用于每个单独类型的数据的输入,输出;

	DataUnit 是一个单独的数据字段;
	BasicData 是一行数据字段;
*********************************************************************/

#pragma once

#include "../LeeConfig.h"


//数据基础单位(就是每个字段的类型,和值);
class DataUnit
{
public:
	enum DataType
	{
		TYPE_CHAR,
		TYPE_SHORT,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_DOUBLE,
		TYPE_LONG,
		TYPE_LONGLONG,
		TYPE_STRING,
		TYPE_ERROR
	} ;

	DataUnit()
		:_type(TYPE_ERROR)
		,_data(NULL)
	{

	}

	DataUnit(const DataUnit& aRight)
	{
		switch (aRight._type)
		{
		case TYPE_CHAR :
			(*this) << *((char*)aRight._data);
			break;

		case TYPE_SHORT :
			(*this) << *((short*)aRight._data);
			break;

		case TYPE_INT:
			(*this) << *((int*)aRight._data);
			break;

		case TYPE_FLOAT :
			(*this) << *((float*)aRight._data);
			break;

		case	TYPE_DOUBLE :
			(*this) << *((double*)aRight._data);
			break;

		case TYPE_LONG :
			(*this) << *((long*)aRight._data);
			break;

		case TYPE_LONGLONG :
			(*this) << *((long long*)aRight._data);
			break;

		case TYPE_STRING :
			(*this) << (char*)aRight._data;
			break;

		default :
			assert(false);
		}
	}

	~DataUnit()
	{
		ReleaseContent();
	}

	//Data import;
	template <typename T>
	DataUnit& operator << (T aVal)
	{
		// type not available
		assert(NULL);

		return *this;
	}

	DataUnit& operator << (char aVal)
	{
		ReleaseContent();

		_type = TYPE_CHAR;
		_data = new char;
		memcpy(_data, &aVal, sizeof(char));

		return *this;
	}

	DataUnit& operator << (short aVal)
	{
		ReleaseContent();

		_type = TYPE_SHORT;
		_data = new short;
		memcpy(_data, &aVal, sizeof(short));

		return *this;
	}

	DataUnit& operator << (int aVal)
	{
		ReleaseContent();

		_data = new int;
		_type = TYPE_INT;
		memcpy(_data, &aVal, sizeof(int));

		return *this;
	}

	DataUnit& operator << (float aVal)
	{
		ReleaseContent();

		_data = new float;
		_type = TYPE_FLOAT;
		memcpy(_data, &aVal, sizeof(float));

		return *this;
	}

	DataUnit& operator << (double aVal)
	{
		ReleaseContent();

		_type = TYPE_DOUBLE;
		_data = new double;
		memcpy(_data, &aVal, sizeof(double));

		return *this;
	}

	DataUnit& operator << (long aVal)
	{
		ReleaseContent();

		_type = TYPE_LONG;
		_data = new long;
		memcpy(_data, &aVal, sizeof(long));
		
		return *this;
	}

	DataUnit& operator << (long long aVal)
	{
		ReleaseContent();

		_type = TYPE_LONGLONG;
		_data = new long long;
		memcpy(_data, &aVal, sizeof(long long));

		return *this;
	}

	DataUnit& operator << (const char *aVal)
	{
		ReleaseContent();

		int len = strlen(aVal);
		_data = new char[len + 1];
		_type = TYPE_STRING;
		memset(_data, 0, (len + 1) * sizeof(char));
		strcpy_s((char*)_data, (len + 1)*sizeof(char), aVal);

		return *this;
	}

	//Data export;
	template <typename T>
	const DataUnit& operator >> (T& aVal) const
	{
		// type not available
		assert(NULL);

		return *this;
	}

	const DataUnit& operator >> (char& aVal) const
	{
		assert(_type == TYPE_CHAR);
		aVal = *((char*)_data);

		return *this;
	}

	const DataUnit& operator >> (short& aVal) const
	{
		assert(_type == TYPE_SHORT);
		aVal = *(short*)_data;

		return *this;
	}

	const DataUnit& operator >> (int& aVal) const
	{
		assert(_type == TYPE_INT);
		aVal = *(int*)_data;

		return *this;
	}

	const DataUnit& operator >> (float& aVal) const
	{
		assert(_type == TYPE_FLOAT);
		aVal = *(float*)_data;

		return *this;
	}

	const DataUnit& operator >> (double& aVal) const
	{
		assert(_type == TYPE_DOUBLE);
		aVal = *(double*)_data;

		return *this;
	}

	const DataUnit& operator >> (long& aVal) const
	{
		assert(_type == TYPE_LONG);
		aVal = *(long*)_data;

		return *this;
	}

	const DataUnit& operator >> (long long& aVal) const
	{
		assert(_type == TYPE_LONGLONG);
		aVal = *(long long*)_data;

		return *this;
	}

	const DataUnit& operator >> (std::string& aVal) const
	{
		assert(_type == TYPE_STRING);
		aVal = (char*)_data;

		return *this;
	}

	//Data convert;
	char ToChar() const
	{
		assert(_type == TYPE_CHAR);
		return *(char*)_data;
	}

	short ToShort() const
	{
		assert(_type == TYPE_SHORT);
		return *(short*)_data;
	}

	int ToInt() const
	{
		assert(_type == TYPE_INT);
		return *(int*)_data;
	}

	float ToFloat() const
	{
		assert(_type == TYPE_FLOAT);
		return *(float*)_data;
	}

	double ToDouble() const
	{
		assert(_type == TYPE_DOUBLE);
		return *(double*)_data;
	}

	long ToLong() const
	{
		assert(_type == TYPE_LONG);
		return *(long*)_data;
	}

	long long ToLongLong() const
	{
		assert(_type == TYPE_LONGLONG);
		return *(long long*)_data;
	}

	std::string ToString() const
	{
		assert(_type == TYPE_STRING);
		return std::string((char*)_data);
	}

	//释放 _data ;
	void ReleaseContent()
	{
		if (_data)
		{
			switch (_type)
			{
			case  TYPE_CHAR :
				delete (char*)_data;
				break;

			case TYPE_SHORT :
				delete (short*)_data;
				break;

			case TYPE_INT:
				delete (int*)_data;
				break;

			case TYPE_FLOAT:
				delete (float*)_data;
				break;

			case TYPE_DOUBLE :
				delete (double*)_data;
				break;

			case TYPE_LONG :
				delete (long*)_data;
				break;

			case TYPE_LONGLONG :
				delete (long long*)_data;
				break;

			case TYPE_STRING:
				delete [] (char*)_data;
				break;
			default:
				// should not arrive here
				assert(NULL);
				break;
			}
		}
	}

protected:

	DataType _type;
	void* _data;
};

//研究了来加注释;
class BasicData
{
public:

	BasicData();
	virtual ~BasicData();
	 
	typedef std::pair<std::string, std::string> DataHead; // key(字段名) , type;

	//重载 [ ] 操作符,使用类似 map 的方式来根据 key 找值;
	const DataUnit& operator [] (const std::string& aKey) const;
	//注意这里是返回的 DataUnit* 是指针哈;
	const DataUnit* GetField(const std::string& aKey) const;
	//解析数据(将文本读取到的数据存入_mapData);
	void ParseData(const std::string& aKey,const std::string& aType, const std::string& aVal);

protected:
	std::map<std::string, DataUnit> _mapData;
};
