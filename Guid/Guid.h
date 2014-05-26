/*!
 * \file Guid.h
 *
 * \author lixiang
 * \date 五月 2014
 *
 * Guid
 */


#pragma once

#include "LeeConfig.h"
#include "PlatForm.h"

#if TARGET_PLATFORM == PLATFORM_LINUX
#include<uuid/uuid.h>
#endif


class Guid														//128bit Guid
{
public:
	struct PtrCmp											//Guid指针地址比较; 
	{
		bool operator()(const Guid* left, const Guid* right) const
		{
			return *left < *right;
		}
	};

	Guid();			

	~Guid();

	Guid(const Guid& guid);

	explicit Guid(const int8* strGuid);								//禁止单参数构造函数的自动类型转换;

	explicit Guid(const string& strGuid);

#if TARGET_PLATFORM == PLATFORM_WINDOWS
	static void Initialize();													//在windows平台下必须调用这个函数 (现在暂时不知道 不调用会有什么错) Init COM库;

	static void Uninitialize();											//UnInit COM库(这个函数要和上面的成对使用);
#endif

	static bool CreateGuid(Guid& guid);							//创建GUID;

	bool IsNull(void);														

	bool IsNull( void )const;													//判断GUID 是否为空(const版本);

	bool Evaluate( const Guid& guid );											//判断GUID 是否相等;

	const int8* ToCStr( void ) const;											//将 GUID 转化为C风格的 const char* 返回 警告!! 内部使用静态字符串数组，所以在sprintf()中如果出现2个以上的tostring调用; 将导致只有最后压栈的GUID数据，前面的GUID都被覆盖了; 这里为什么要使用静态字符数组而有这个BUG?难道是为了不让它不停的定义提高效率?

	string ToStr( void ) const;												//将 GUID 转化为 string 返回;

	void MakeSqlString( int8** buffer );										//将GUID转换为 sql 语句的字符串;(这个函数有改进的空间)

	void MakeGuid( const int8* szGuid );										//将字符形式的GUID 转化为 值形式的GUID;

	void Make( const string &str);												//同上 参数不一样;

	Guid& operator = (const Guid& guid);									//重载 = 操作符;

	bool operator == (const Guid& guid) const;							//重载 == 操作符;

	bool operator != (const Guid& guid) const;							//重载 != 操作符;

	bool operator < (const Guid& guid) const;							//重载 < 操作符;

	bool operator > (const Guid& guid) const;							//重载 >  操作符;

	bool CharConvertValue(const char* szValue, int32& retValue);		//将字符转化为实值;

	static Guid GUID_INVALID;													//无效的GUID(全为0) 作用是用作Guid类的初始化;

private:
	uint32	_Data1;
	uint16	_Data2;
	uint16	_Data3;
	uint8	_Data4[8];
};

const Guid NULL_GUID = Guid::GUID_INVALID;