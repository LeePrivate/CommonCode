#include "Guid.h"

#if TARGET_PLATFORM == PLATFORM_WINDOWS
#include <Windows.h>
#include <objbase.h>
#endif

Guid Guid::GUID_INVALID;                                             //如果没有这句会报     1>Util_D.lib(LeeGuid.obj) : error LNK2001: 无法解析的外部符号 "public: static class Lee::Guid Lee::Guid::GUID_INVALID" (?GUID_INVALID@Guid@Lee@@2V12@A)

Guid::Guid()
{
	memset(this, 0, sizeof(Guid));
}

Guid::~Guid()
{

}

Guid::Guid(const Guid& guid)
{
	if (&guid != this)
	{
		memcpy(this, &guid, sizeof(Guid));
	}
}

Guid::Guid(const int8* strGuid)
{
	memset(this, 0, sizeof(Guid));
	if (strGuid != NULL && strlen(strGuid) == 38)					//这里38的意思是 Guid的字符串表现形式是38个字符组成,格式为 {xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}
	{
		int8 tmpStr[37] = "";
		memcpy(tmpStr, strGuid + 1, 36);
		int32 curPos = 0;
		//data1
		for (int32 i = 0 ; i < 8 ; ++i)
		{
			int32 value = tmpStr[i];
			if (!CharConvertValue(&tmpStr[i], value))
			{
				memset(this, 0, sizeof(Guid));
				return;
			}
			value = value << (28 - (4*i));
			_Data1 |= value;
		}
		curPos += 9;  //+=9是应为有一个 "-"字符

		//data2
		for (int32 i = curPos ; i < (curPos + 4) ; ++i)
		{
			int32 value = tmpStr[i];
			if (!CharConvertValue(&tmpStr[i], value))
			{
				memset(this, 0, sizeof(Guid));
				return;
			}
			value = value << (12 - (4* (i - curPos)));
			_Data2 |= value;
		}
		curPos += 5;

		//data3
		for (int32 i = curPos ; i < (curPos + 4) ; ++i)
		{
			int32 value = tmpStr[i];
			if (!CharConvertValue(&tmpStr[i], value))
			{
				memset(this, 0, sizeof(Guid));
				return;
			}
			value = value << ( 12 - ( 4 * ( i - curPos ) ) );
			_Data3 |= value;
		}
		curPos += 5;

		//data4 --- 1
		int32 tmpData4Pos = 0;
		for (int32 i = curPos ; i < (curPos + 4) ; ++i)
		{
			//高位
			int32 value = tmpStr[i];
			if (!CharConvertValue(&tmpStr[i], value))
			{
				memset(this, 0, sizeof(Guid));
				return;
			}
			_Data4[tmpData4Pos] |= value << 4;
			i++;

			//地位
			value = tmpStr[i];
			if (!CharConvertValue(&tmpStr[i], value))
			{
				memset(this, 0, sizeof(Guid));
				return;
			}
			_Data4[tmpData4Pos] |= value;
			tmpData4Pos++;
		}
		curPos += 5;

		//data4 --- 2
		for (int32 i = curPos ; i < (curPos + 12) ; ++i)
		{
			//高位
			int32 value = tmpStr[i];
			if (!CharConvertValue(&tmpStr[i], value))
			{
				memset(this, 0, sizeof(Guid));
				return;
			}
			_Data4[tmpData4Pos] |= value << 4;
			++i;

			//低位
			value = tmpStr[i];
			if (!CharConvertValue(&tmpStr[i], value))
			{
				memset(this, 0, sizeof(Guid));
				return;
			}
			_Data4[tmpData4Pos] |= value;
			++tmpData4Pos;
		}
	}
}

Guid::Guid(const string& strGuid)
{
	memset( this, 0, sizeof(Guid) );
	if( strGuid.size() == 38 )
	{
		int8 tmpStr[37] = "";
		memcpy( tmpStr, &strGuid[1], 36 );
		int32 curPos = 0;
		// data1
		for( int32 i = 0; i < 8; i++ )
		{
			int32 value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			value = value << ( 28 - ( 4 * i ) );
			_Data1 |= value;
		}
		curPos += 9;

		// data2
		for( int32 i = curPos; i <  ( curPos + 4 ); i++ )
		{
			int32 value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			value = value << ( 12 - ( 4 * ( i - curPos ) ) );
			_Data2 |= value;
		}
		curPos += 5;

		//data3
		for( int32 i = curPos; i <  ( curPos + 4 ); i++ )
		{
			int32 value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			value = value << ( 12 - ( 4 * ( i - curPos ) ) );
			_Data3 |= value;
		}
		curPos += 5;

		//data4 ---- 1
		int32 tmpData4Pos = 0;
		for( int32 i = curPos; i < ( curPos + 4 ); i++ )
		{
			// 高位
			int32 value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			_Data4[tmpData4Pos] |= value << 4;
			i++;

			//低位
			value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			_Data4[tmpData4Pos] |= value;
			tmpData4Pos++;
		}
		curPos += 5;

		//data4 ---- 2
		for( int32 i = curPos; i < ( curPos + 12 ); i++ )
		{
			// 高位
			int32 value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			_Data4[tmpData4Pos] |= value << 4;
			i++;

			//低位
			value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			_Data4[tmpData4Pos] |= value;
			tmpData4Pos++;
		}
	}
}

bool Guid::CharConvertValue(const char* szValue, int32& retValue)
{
	if (!szValue)
	{
		return false;									//这里原来是true,如果使用时候有错检查这里;
	}
	if( *szValue >= '0' && *szValue <= '9' )
	{
		retValue = *szValue - 0x30;
		return true;
	}
	else if( *szValue >= 'A' && *szValue <= 'F' )
	{
		retValue = *szValue - 0x41 + 10;
		return true;
	}
	else if( *szValue >= 'a' && *szValue <= 'f' )
	{
		retValue = *szValue - 0x61 + 10;
		return true;
	}
	return false;
}

#if TARGET_PLATFORM == PLATFORM_WINDOWS
void Guid::Initialize()
{
	::CoInitialize( NULL );
}

void Guid::Uninitialize()
{
	::CoUninitialize();
}
#endif

bool Guid::CreateGuid(Guid& guid)
{
#if TARGET_PLATFORM == PLATFORM_WINDOWS
	if( FAILED( CoCreateGuid( ( GUID* )( &guid ) ) ) )
	{
		return false;
	}	
#else
	uuid_generate( ( uint8* ) &guid );
#endif
	return true;
}

bool Guid::IsNull(void)
{
	return *this == NULL_GUID;
}

bool Guid::IsNull(void) const
{
	return *this == NULL_GUID;
}

bool Guid::Evaluate(const Guid& guid)
{
	return ( *this == guid );
}

const int8* Guid::ToCStr(void) const
{
	static int8 strGuid[40] = {0};
	sprintf_s( strGuid, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
		_Data1, _Data2, _Data3, _Data4[0], _Data4[1], _Data4[2], _Data4[3], 
		_Data4[4], _Data4[5], _Data4[6], _Data4[7] );
	return strGuid;
}

std::string Guid::ToStr(void) const
{
	return ToCStr();
}

void Guid::MakeSqlString(int8** buffer)
{
	if( !buffer )
		return;
	sprintf_s( *buffer, sizeof(*buffer), "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		_Data1, _Data2, _Data3, _Data4[0], _Data4[1], _Data4[2], _Data4[3], 
		_Data4[4], _Data4[5], _Data4[6], _Data4[7] );
}

void Guid::MakeGuid(const int8* szGuid)
{
	memset( this, 0, sizeof(Guid) );												
	if( szGuid != NULL && strlen(szGuid) == 38 )							
	{
		int8 tmpStr[37] = "";
		memcpy( tmpStr, szGuid + 1, 36 );										
		int32 curPos = 0;
		//data1
		for( int32 i = 0; i < 8; i++ )													
		{
			int32 value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value ) )
			{
				memset(this, 0, sizeof(Guid) );
				return;
			}
			value = value << (28 - (4*i));
			_Data1 |= value;
		}
		curPos += 9;

		//data2
		for( int32 i = curPos; i < (curPos + 4); i++ )
		{
			int32 value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value ) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			value = value << ( 12 - ( 4 * ( i - curPos ) ) );
			_Data2 |= value;
		}
		curPos += 5;

		//data3
		for( int32 i = curPos; i < ( curPos + 4); i++ )
		{
			int32 value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value ) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			value = value << ( 12 - ( 4 * ( i - curPos ) ) );
			_Data3 |= value;
		}
		curPos += 5;

		//data4 ---- 1
		int32 tmpData4Pos = 0;
		for( int32 i = curPos; i < ( curPos + 4 ); i++ )
		{
			// 高位
			int32 value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			_Data4[tmpData4Pos] |= value << 4;
			i++;

			//低位
			value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			_Data4[tmpData4Pos] |= value;
			tmpData4Pos++;
		}
		curPos += 5;

		//data4 ---- 2
		for( int32 i = curPos; i < ( curPos + 12 ); i++ )											
		{
			// 高位
			int32 value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			_Data4[tmpData4Pos] |= value << 4;
			i++;

			//低位
			value = tmpStr[i];
			if( !CharConvertValue( &tmpStr[i], value) )
			{
				memset( this, 0, sizeof(Guid) );
				return;
			}
			_Data4[tmpData4Pos] |= value;
			tmpData4Pos++;
		}
	}
}

void Guid::Make(const string &str)
{
	MakeGuid( str.c_str() );
}

Guid& Guid::operator=(const Guid& guid)
{
	if (&guid != this)
	{
		memcpy(this, &guid, sizeof(Guid));
	}
	return *this;
}

bool Guid::operator==(const Guid& guid) const
{
	return memcmp(this, &guid, sizeof(Guid)) == 0;
}

bool Guid::operator!=(const Guid& guid) const
{
	return !(operator == (guid));
}

bool Guid::operator<(const Guid& guid) const
{
	return memcmp(this, &guid, sizeof(Guid)) < 0;
}

bool Guid::operator>(const Guid& guid) const
{
	return memcmp(this, &guid, sizeof(Guid)) > 0;
}






