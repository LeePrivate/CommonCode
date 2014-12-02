/*!
 * \file Stream.h
 *
 * \author lixiang
 * \date 五月 2014
 *
 * 数据流的操作 注意 如果使用这套方法,不能给于 const 属性的参数,以后来添加 const 属性参数的重载;
 */



#pragma once

#include "Guid/Guid.h"
#include "TypeConvert/TypeConvert.h"

//错误枚举;
typedef enum
{
	EStreamError_Error,					
	EStreamError_OK,
	EStreamError_BufferFull, 
	EStreamError_BadArg,
}EStreamError;

//数据流接口;
class BaseStream
{
public:
	BaseStream();

	virtual ~BaseStream();

	EStreamError GetError() const;

	bool IsOK() const;

	virtual BaseStream& BytesSerialize(const void* data, size_t size) = 0;			//字节序列化 is << data;

	virtual BaseStream& BytesDeserialize(void* data, size_t size) = 0;				//字节反序列化 os >> data;

	virtual size_t GetOffset() const = 0;															//得到偏移量;

	virtual size_t GetSize() const = 0;																//总大小;

	virtual size_t GetSpace() const;																	//得到空闲大小;

	BaseStream& operator << (bool value)														//(bool)重载 << 操作符;
	{
		uint8 i = (value ? 1 : 0);	
		return BytesSerialize(&i, sizeof(uint8));
	}

	BaseStream& operator >> (bool& value)													//(bool)重载 >> 操作符;
	{
		uint8 i = 0;
		BytesDeserialize(&i, sizeof(uint8));
		value = (i == 1);
		return *this;
	}

	BaseStream& operator << (const char* str)	//这个重载只有 << 没有 >>的原因是如果用char* 作为接收体会不安全;
	{
		if (str == NULL)
		{
			_eStreamError = EStreamError_BadArg;
			return *this;
		}
		uint32 size = (uint32)strlen(str);
		BytesSerialize(&size, sizeof(uint32));	//这里放一个长度是为了去除的时候知道要分配多少空间;
		return BytesSerialize(str, size);
	}

	BaseStream& operator << (const string& str)
	{
		//保持64位与32位的一致性, 如果data.size() > MAX_UINT, 应该已经出问题了;
		uint32 size = (uint32)str.length();
		BytesSerialize(&size, sizeof(uint32));
		return BytesSerialize(str.data(), size); //这里用str.data()是为了返回的指针不带\0
	}

	BaseStream& operator >> (string& str)
	{
		uint32 size = 0;
		BytesDeserialize(&size, sizeof(uint32));
		str.clear();
		if (size > 0)
		{
			str.insert(0, size, 0);
			return BytesDeserialize(&str[0], size);
		}
	}

	BaseStream& operator << (const Guid& guid)
	{
		//保持64位与32位的一致性,如果data.size() > MAX_UINT,应该已经出问题了;
		uint32 size = (uint32)sizeof(Guid);
		return BytesSerialize(&guid, size);
	}

	BaseStream& operator >> (Guid& guid)
	{
		uint32 size = 16;
		//BaseStream& bs = BytesDeserialize(&guid, size);		//这两行是原来的,如果有问题改回来;
		//return bs;
		return BytesDeserialize(&guid, size);
	}

//各种类型 Read 操作 >> 宏定义;
#define BASESTREAM_READ( valueType )\
	BaseStream& operator >> ( valueType& value )\
	{\
		return BytesDeserialize( &value, sizeof(valueType) );\
	}

	BASESTREAM_READ( int8 );
	BASESTREAM_READ( uint8 );

	BASESTREAM_READ( int16 );
	BASESTREAM_READ( uint16 );

	BASESTREAM_READ( int32 );
	BASESTREAM_READ( uint32 );

	BASESTREAM_READ( long );
	BASESTREAM_READ( unsigned long );

	BASESTREAM_READ( int64 );
	BASESTREAM_READ( uint64 );

	BASESTREAM_READ( float );
	BASESTREAM_READ( double );

//各种类型 Write 操作 << 宏定义;
#define BASESTREAM_WRITE( valueType )\
	BaseStream& operator << ( valueType value )\
	{\
		return BytesSerialize( &value, sizeof(valueType) );\
	}\

	BASESTREAM_WRITE( int8 );
	BASESTREAM_WRITE( uint8 );

	BASESTREAM_WRITE( int16 );
	BASESTREAM_WRITE( uint16 );

	BASESTREAM_WRITE( int32 );
	BASESTREAM_WRITE( uint32 );

	BASESTREAM_WRITE( long );
	BASESTREAM_WRITE( unsigned long );

	BASESTREAM_WRITE( int64 );
	BASESTREAM_WRITE( uint64 );

	BASESTREAM_WRITE( float );
	BASESTREAM_WRITE( double );

	//这之下是各种习惯的读取,存贮方式------------------------------;
	//int8;
	int8 ReadInt8()
	{
		int8 v = 0;
		BytesDeserialize( &v, sizeof(int8) );
		return v;
	}
	int8 GetInt8()
	{
		int8 v = 0;
		BytesDeserialize( &v, sizeof(int8) );
		return v;
	}

	void WriteInt8( int8 v )
	{
		BytesSerialize( &v, sizeof(int8) );
	}
	void SetInt8( int8 v )
	{
		BytesSerialize( &v, sizeof(int8) );
	}

	//uint8
	uint8 ReadUint8()
	{
		uint8 v = 0;
		BytesDeserialize( &v, sizeof(uint8) );
		return v;
	}
	uint8 GetUint8()
	{
		uint8 v = 0;
		BytesDeserialize( &v, sizeof(uint8) );
		return v;
	}

	void WriteUint8( uint8 v )
	{
		BytesSerialize( &v, sizeof(uint8) );
	}
	void SetUint8( uint8 v )
	{
		BytesSerialize( &v, sizeof(uint8) );
	}

	//int16
	int16 ReadInt16()
	{
		int16 v = 0;
		BytesDeserialize(&v, sizeof(int16));
		return v;
	}
	int16 GetInt16()
	{
		int16 v = 0;
		BytesDeserialize(&v, sizeof(int16));
		return v;
	}

	void WriteInt16(int16 v)
	{
		BytesSerialize(&v, sizeof(int16));
	}
	void SetInt16(int16 v)
	{
		BytesSerialize(&v, sizeof(int16));
	}

	//uint16
	uint16 ReadUint16()
	{
		uint16 v = 0;
		BytesDeserialize(&v, sizeof(uint16));
		return v;
	}
	uint16 GetUint16()
	{
		uint16 v = 0;
		BytesDeserialize(&v, sizeof(uint16));
		return v;
	}

	void WriteUint16(uint16 v)
	{
		BytesSerialize(&v, sizeof(uint16));
	}
	void SetUint16(uint16 v)
	{
		BytesSerialize(&v, sizeof(uint16));
	}

	//int32
	int32 ReadInt()
	{
		int32 v = 0;
		BytesDeserialize( &v, sizeof(int32) );
		return v;
	}
	int32 GetInt()
	{
		int v = 0;
		BytesDeserialize( &v, sizeof(int32) );
		return v;
	}

	void WriteInt( int32 v )
	{
		BytesSerialize( &v, sizeof(int32) );
	}
	void SetInt( int32 v )
	{
		BytesSerialize( &v, sizeof(int32) );
	}

	//uint32
	uint32 ReadUint()
	{
		uint32 v = 0;
		BytesDeserialize( &v, sizeof(uint32) );
		return v;
	}
	uint32 GetUint()
	{
		uint32 v = 0;
		BytesDeserialize( &v, sizeof(uint32) );
		return v;
	}

	void WriteUint( uint32 v )
	{
		BytesSerialize( &v, sizeof(uint32) );
	}
	void SetUint( uint32 v )
	{
		BytesSerialize( &v, sizeof(uint32) );
	}

	//long
	long ReadLong()
	{
		long v;
		BytesDeserialize(&v, sizeof(long));
		return v;
	}
	long GetLong()
	{
		long v;
		BytesDeserialize(&v, sizeof(long));
		return v;
	}
	
	void WriteLong(long v)
	{
		BytesSerialize(&v, sizeof(long));
	}
	void SetLong(long v)
	{
		BytesSerialize(&v, sizeof(long));
	}

	//unsigned long
	unsigned long ReadULong()
	{
		unsigned long v;
		BytesDeserialize(&v, sizeof(unsigned long));
		return v;
	}
	unsigned long GetULong()
	{
		unsigned long v;
		BytesDeserialize(&v, sizeof(unsigned long));
		return v;
	}

	void WriteULong(unsigned long v)
	{
		BytesSerialize(&v, sizeof(unsigned long));
	}
	void SetULong(unsigned long v)
	{
		BytesSerialize(&v, sizeof(unsigned long));
	}

	//int64
	int64 ReadInt64()
	{
		int64 v = 0;
		BytesDeserialize(&v, sizeof(int64));
		return v;
	}
	int64 GetInt64()
	{
		int64 v = 0;
		BytesDeserialize(&v, sizeof(int64));
	}

	void WriteInt64(int64 v)
	{
		BytesSerialize(&v, sizeof(int64));
	}
	void SetInt64(int64 v)
	{
		BytesSerialize(&v, sizeof(int64));
	}

	//uint64
	uint64 ReadUint64()
	{
		uint64 v = 0;
		BytesDeserialize( &v, sizeof(uint64) );
		return v;
	}
	uint64 GetUint64()
	{
		uint64 v = 0;
		BytesDeserialize( &v, sizeof(uint64) );
		return v;
	}

	void WriteUint64( uint64 v )
	{
		BytesSerialize( &v, sizeof(uint64) );
	}
	void SetUint64( uint64 v )
	{
		BytesSerialize( &v, sizeof(uint64) );
	}

	//float
	float ReadFloat()
	{
		float v = 0;
		BytesDeserialize( &v, sizeof(float) );
		return v;
	}
	float GetFloat()
	{
		float v = 0;
		BytesDeserialize( &v, sizeof(float) );
		return v;
	}

	void WriteFloat( float v )
	{
		BytesSerialize( &v, sizeof(float) );
	}
	void SetFloat( float v )
	{
		BytesSerialize( &v, sizeof(float) );
	}

	//double
	double ReadDouble()
	{
		double v = 0;
		BytesDeserialize( &v, sizeof(double) );
		return v;
	}
	double GetDouble()
	{
		double v = 0;
		BytesDeserialize( &v, sizeof(double) );
		return v;
	}

	void WriteDouble( double v )
	{
		BytesSerialize( &v, sizeof(double) );
	}
	void SetDouble( double v )
	{
		BytesSerialize( &v, sizeof(double) );
	}

	//bool
	bool ReadBool()
	{
		uint8 v = 0;
		BytesDeserialize(&v, sizeof(uint8));
		return (v == 0 ? false : true); 
	}
	bool GetBool()
	{
		uint8 v = 0;
		BytesDeserialize( &v, sizeof(uint8) );
		return (v == 0 ? false : true);
	}

	void WriteBool(bool v)
	{
		uint8 value = (v == true ? 1 : 0);
		BytesSerialize(&value, sizeof(uint8));
	}
	void SetBool(bool v)
	{
		uint8 value = (v == true ? 1 : 0);
		BytesSerialize(&value, sizeof(uint8));
	}

	//string
	std::string ReadStr()
	{
		uint32 size = 0;
		BytesDeserialize(&size, sizeof(uint32));
		std::string str;
		str.clear();
		if (size > 0)
		{
			str.insert(0, size, 0);
			BytesDeserialize(&(str[0]), size);
		}
		return str;
	}
	std::string GetStr()
	{
		uint32 size = 0;
		BytesDeserialize(&size, sizeof(uint32));
		std::string str;
		str.clear();
		if (size > 0)
		{
			str.insert(0, size, 0);
			BytesDeserialize(&(str[0]), size);
		}
		return str;
	}

	void WriteStr(const std::string str)
	{
		uint32 size = (uint32)str.length();
		BytesSerialize(&size, sizeof(uint32));
		BytesSerialize(str.data(), size);
	}
	void SetStr(const std::string str)
	{
		uint32 size = (uint32)str.length();
		BytesSerialize(&size, sizeof(uint32));
		BytesSerialize(str.data(), size);
	}

	//Guid
	Guid ReadGuid()
	{
		Guid guid;
		uint32 size = (uint32)sizeof(Guid);
		BytesDeserialize( &guid, size );
		return guid;
	}
	Guid GetGuid()
	{
		Guid guid;
		uint32 size = (uint32)sizeof(Guid);
		BytesDeserialize( &guid, size );
		return guid;
	}

	void WriteGuid( const Guid& guid )
	{
		uint32 size = (uint32)sizeof(Guid);
		BytesSerialize( &guid, size );
	}
	void SetGuid( const Guid& guid )
	{
		uint32 size = (uint32)sizeof(Guid);
		BytesSerialize( &guid, size );
	}

	//For sql
	std::string ReadText()
	{
		return ReadStr();
	}
	std::string GetText()
	{
		return ReadStr();
	}

	
protected:
	EStreamError _eStreamError;
};

//--------------------------------------我是不让你眼睛看花的好心分割线--------------------------------------------------

//序列化模版
template<typename T>
inline BaseStream& operator << (BaseStream& os, const T& data)
{
	data.Serialize(os);
	return os;
}

template<typename T>
inline BaseStream& operator >> (BaseStream& is, T& data)
{
	data.Deserialize(is);
	return is;
}

//vector序列化 我觉得BaseStream 应该改为实际使用的子类,用到来改;
template<typename T>
inline BaseStream& operator << (BaseStream& os, const std::vector<T>& data)  //这个函数我觉得有点问题,应为BaseStream << >>操作符 里面的Serialize和Deserialize函数是纯虚的,下面这一系列的函数模版我觉得都应该使用继承于BaseStream的类来做左操作数以后使用的时候再来研究有问题再改;
{
	//保持64位与32位的一致性,如果data.size() > MAX_UINT,应该已经出问题了;
	uint32 size = data.size();
	os << (uint32)size;
	for (uint32 i = 0 ; i < size ; ++i)
	{
		os << data[i];
	}
	return os;
}

template<typename T>
inline BaseStream& operator >> (BaseStream& is, std::vector<T>& data)
{
	uint32 size = 0;
	is >> size;
	data.resize((size_t)size);
	for (uint32 i = 0 ; i < size ; ++i)
	{
		is >> data[i];
	}
	return is;
}

//map 序列化 我觉得BaseStream 应该改为实际使用的子类,用到来改;;
template<typename K, typename V>
inline BaseStream& operator << (BaseStream& os, const std::map<K, V>& data)
{
	//保持64位与32位的一致性,如果data.size() > MAX_UINT,应该已经出问题了;
	size_t size = data.size();
	os << (uint32)size;
	typename std::map<K, V>::const_iterator c_iter;
	for (c_iter = data.begin() ; c_iter != data.end() ; ++c_iter)
	{
		os << (*c_iter).first < (*c_iter).second;
	}
	return os;
}

template<typename K, typename V>
inline BaseStream& operator >> (BaseStream& is, const std::map<K, V>& data)
{
	uint32 size = 0;
	is >> size;
	data.clear();
	for (uint32 i = 0 ; i < size ; ++i)
	{
		K key;
		is >> Key >> data[Key];
	}
	return is;
}

//固定缓存的数据流;有需要添加拷贝构造,重载 = 等函数;
class Stream : public BaseStream
{
public:
	//外部缓存;
	Stream(uint8* pBuffer, size_t size);

	//内部分配内存;
	Stream(size_t size);

	virtual ~Stream(void);

	//释放内存;
	void ReleaseBuffer();

	//得到偏移量;
	virtual size_t GetOffset() const;

	//总大小;
	virtual size_t GetSize() const;

	//指针接口;
	virtual uint8* GetBuffer() const;

	uint8* GetOffsetPointer();

	void ResetPointer();

	void SetBuffer(uint8* pBuffer, size_t size);

	//数据流中间设置数据;
	bool SetData(size_t pos, const void* data, size_t size);

	//偏移向前;
	bool Ignore(size_t size);

	//实现父类纯虚 序列化 is << data;
	virtual BaseStream& BytesSerialize(const void* data, size_t size);

	//实现父类纯虚 反序列化 os >> data;
	virtual BaseStream& BytesDeserialize(void* data, size_t size);

	//序列化自己;
	virtual void Serialize(BaseStream& streamTo) const;

	//反序列化自己;
	virtual void Deserialize(BaseStream& streamForm);

protected:
	uint8*	_Buffer;							//起始地址;
	uint8*	_Pointer;						//当前地址;
	size_t	_Size;							//总大小;
};

//固定大小的缓存流;
template<uint32 bufferSize>
class BufferStream : public Stream
{
public:
	BufferStream()
		:Stream(_MemBuffer, bufferSize)
	{
		memset(_MemBuffer, 0, sizeof(_MemBuffer));
	}

	virtual ~BufferStream();

protected:
	uint8 _MemBuffer[bufferSize];
};

//动态大小的数据流;
class StringStream : public BaseStream
{
public:
	StringStream();

	virtual ~StringStream();

	//偏移;
	virtual size_t GetOffset() const;

	//总大小;
	virtual size_t GetSize() const;

	string& GetBuffer();

	const string& GetBuffer() const;

	void ResetOffset();

	//数据流的中间设置数据;
	bool SetData(size_t pos, const void* data, size_t size);

	//序列化 is << data;
	virtual BaseStream& BytesSerialize(const void* data, size_t size);

	//反序列化 os >> data;
	virtual BaseStream& BytesDeserialize(void* data, size_t size);

protected:
	string	_strBuffer;
	size_t	_Offset;
};

//宏
//1个成员变量;
#define SERIALIZE_STRUCT_1(structName, atgType1, arg1)\
struct structName\
{\
	argType1 arg1;\
	virtual void Serialize(BaseStream& os) const		{os << arg1;}\
	virtual void Deserialize(BaseStream& is)		{is >> arg1;}\
}

//2个成员变量;
#define SERIALIZE_STRUCT_2(structName, argType1, arg1, argType2, arg2)\
struct structName\
{\
	argType1 arg1;\
	argType2 arg2;\
	virtual void Serialize(BaseStream& os) const		{os << arg1 << arg2;}\
	virtual void Deserialize(BaseStream& is)		{is >> arg1 >> arg2;}\
}

//3个成员变量;
#define SERIALIZE_STRUCT_3( structName, argType1, arg1, argType2, arg2, argType3, arg3 )\
struct structName\
{\
	argType1 arg1;\
	argType2 arg2;\
	argType3 arg3;\
	virtual void Serialize( BaseStream& os ) const		{ os << arg1 << arg2 << arg3; }\
	virtual void Deserialize( BaseStream& is ) 			{ is >> arg1 >> arg2 >> arg3; }\
}