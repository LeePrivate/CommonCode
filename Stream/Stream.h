/*!
 * \file Stream.h
 *
 * \author lixiang
 * \date ���� 2014
 *
 * �������Ĳ��� ע�� ���ʹ�����׷���,���ܸ��� const ���ԵĲ���,�Ժ������ const ���Բ���������;
 */



#pragma once

#include "Guid/Guid.h"
#include "TypeConvert/TypeConvert.h"

//����ö��;
typedef enum
{
	EStreamError_Error,					
	EStreamError_OK,
	EStreamError_BufferFull, 
	EStreamError_BadArg,
}EStreamError;

//�������ӿ�;
class BaseStream
{
public:
	BaseStream();

	virtual ~BaseStream();

	EStreamError GetError() const;

	bool IsOK() const;

	virtual BaseStream& BytesSerialize(const void* data, size_t size) = 0;			//�ֽ����л� is << data;

	virtual BaseStream& BytesDeserialize(void* data, size_t size) = 0;				//�ֽڷ����л� os >> data;

	virtual size_t GetOffset() const = 0;															//�õ�ƫ����;

	virtual size_t GetSize() const = 0;																//�ܴ�С;

	virtual size_t GetSpace() const;																	//�õ����д�С;

	BaseStream& operator << (bool value)														//(bool)���� << ������;
	{
		uint8 i = (value ? 1 : 0);	
		return BytesSerialize(&i, sizeof(uint8));
	}

	BaseStream& operator >> (bool& value)													//(bool)���� >> ������;
	{
		uint8 i = 0;
		BytesDeserialize(&i, sizeof(uint8));
		value = (i == 1);
		return *this;
	}

	BaseStream& operator << (const char* str)	//�������ֻ�� << û�� >>��ԭ���������char* ��Ϊ������᲻��ȫ;
	{
		if (str == NULL)
		{
			_eStreamError = EStreamError_BadArg;
			return *this;
		}
		uint32 size = (uint32)strlen(str);
		BytesSerialize(&size, sizeof(uint32));	//�����һ��������Ϊ��ȥ����ʱ��֪��Ҫ������ٿռ�;
		return BytesSerialize(str, size);
	}

	BaseStream& operator << (const string& str)
	{
		//����64λ��32λ��һ����, ���data.size() > MAX_UINT, Ӧ���Ѿ���������;
		uint32 size = (uint32)str.length();
		BytesSerialize(&size, sizeof(uint32));
		return BytesSerialize(str.data(), size); //������str.data()��Ϊ�˷��ص�ָ�벻��\0
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
		//����64λ��32λ��һ����,���data.size() > MAX_UINT,Ӧ���Ѿ���������;
		uint32 size = (uint32)sizeof(Guid);
		return BytesSerialize(&guid, size);
	}

	BaseStream& operator >> (Guid& guid)
	{
		uint32 size = 16;
		//BaseStream& bs = BytesDeserialize(&guid, size);		//��������ԭ����,���������Ļ���;
		//return bs;
		return BytesDeserialize(&guid, size);
	}

//�������� Read ���� >> �궨��;
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

//�������� Write ���� << �궨��;
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

	//��֮���Ǹ���ϰ�ߵĶ�ȡ,������ʽ------------------------------;
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

//--------------------------------------���ǲ������۾������ĺ��ķָ���--------------------------------------------------

//���л�ģ��
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

//vector���л� �Ҿ���BaseStream Ӧ�ø�Ϊʵ��ʹ�õ�����,�õ�����;
template<typename T>
inline BaseStream& operator << (BaseStream& os, const std::vector<T>& data)  //��������Ҿ����е�����,ӦΪBaseStream << >>������ �����Serialize��Deserialize�����Ǵ����,������һϵ�еĺ���ģ���Ҿ��ö�Ӧ��ʹ�ü̳���BaseStream����������������Ժ�ʹ�õ�ʱ�������о��������ٸ�;
{
	//����64λ��32λ��һ����,���data.size() > MAX_UINT,Ӧ���Ѿ���������;
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

//map ���л� �Ҿ���BaseStream Ӧ�ø�Ϊʵ��ʹ�õ�����,�õ�����;;
template<typename K, typename V>
inline BaseStream& operator << (BaseStream& os, const std::map<K, V>& data)
{
	//����64λ��32λ��һ����,���data.size() > MAX_UINT,Ӧ���Ѿ���������;
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

//�̶������������;����Ҫ��ӿ�������,���� = �Ⱥ���;
class Stream : public BaseStream
{
public:
	//�ⲿ����;
	Stream(uint8* pBuffer, size_t size);

	//�ڲ������ڴ�;
	Stream(size_t size);

	virtual ~Stream(void);

	//�ͷ��ڴ�;
	void ReleaseBuffer();

	//�õ�ƫ����;
	virtual size_t GetOffset() const;

	//�ܴ�С;
	virtual size_t GetSize() const;

	//ָ��ӿ�;
	virtual uint8* GetBuffer() const;

	uint8* GetOffsetPointer();

	void ResetPointer();

	void SetBuffer(uint8* pBuffer, size_t size);

	//�������м���������;
	bool SetData(size_t pos, const void* data, size_t size);

	//ƫ����ǰ;
	bool Ignore(size_t size);

	//ʵ�ָ��ി�� ���л� is << data;
	virtual BaseStream& BytesSerialize(const void* data, size_t size);

	//ʵ�ָ��ി�� �����л� os >> data;
	virtual BaseStream& BytesDeserialize(void* data, size_t size);

	//���л��Լ�;
	virtual void Serialize(BaseStream& streamTo) const;

	//�����л��Լ�;
	virtual void Deserialize(BaseStream& streamForm);

protected:
	uint8*	_Buffer;							//��ʼ��ַ;
	uint8*	_Pointer;						//��ǰ��ַ;
	size_t	_Size;							//�ܴ�С;
};

//�̶���С�Ļ�����;
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

//��̬��С��������;
class StringStream : public BaseStream
{
public:
	StringStream();

	virtual ~StringStream();

	//ƫ��;
	virtual size_t GetOffset() const;

	//�ܴ�С;
	virtual size_t GetSize() const;

	string& GetBuffer();

	const string& GetBuffer() const;

	void ResetOffset();

	//���������м���������;
	bool SetData(size_t pos, const void* data, size_t size);

	//���л� is << data;
	virtual BaseStream& BytesSerialize(const void* data, size_t size);

	//�����л� os >> data;
	virtual BaseStream& BytesDeserialize(void* data, size_t size);

protected:
	string	_strBuffer;
	size_t	_Offset;
};

//��
//1����Ա����;
#define SERIALIZE_STRUCT_1(structName, atgType1, arg1)\
struct structName\
{\
	argType1 arg1;\
	virtual void Serialize(BaseStream& os) const		{os << arg1;}\
	virtual void Deserialize(BaseStream& is)		{is >> arg1;}\
}

//2����Ա����;
#define SERIALIZE_STRUCT_2(structName, argType1, arg1, argType2, arg2)\
struct structName\
{\
	argType1 arg1;\
	argType2 arg2;\
	virtual void Serialize(BaseStream& os) const		{os << arg1 << arg2;}\
	virtual void Deserialize(BaseStream& is)		{is >> arg1 >> arg2;}\
}

//3����Ա����;
#define SERIALIZE_STRUCT_3( structName, argType1, arg1, argType2, arg2, argType3, arg3 )\
struct structName\
{\
	argType1 arg1;\
	argType2 arg2;\
	argType3 arg3;\
	virtual void Serialize( BaseStream& os ) const		{ os << arg1 << arg2 << arg3; }\
	virtual void Deserialize( BaseStream& is ) 			{ is >> arg1 >> arg2 >> arg3; }\
}