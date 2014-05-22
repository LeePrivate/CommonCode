#include "TypeConvert.h"
#include <boost/lexical_cast.hpp>

int8 TypeConvert::ToInt8(const char* str)
{
	if (!str)
	{
		return (int8)0;
	}
	return static_cast<int8>(strtol(str, NULL, 10));
}

uint8 TypeConvert::ToUint8(const char* str)
{
	if (!str)
	{
		return (uint8)0;
	}
	return static_cast<uint8>(strtoul(str, NULL, 10));
}

int16 TypeConvert::ToInt16(const char* str)
{
	if (!str)
	{
		return (int16)0;
	}
	return static_cast<int16>(strtol(str, NULL, 10));
}

uint16 TypeConvert::ToUint16(const char* str)
{
	if (!str)
	{
		return (uint16)0;
	}
	return static_cast<uint16>(strtoul(str, NULL, 10));
}

int32 TypeConvert::ToInt32(const char* str)
{
	if (!str)
	{
		return 0;
	}
	return static_cast<int32>(strtol(str, NULL, 10));
}

uint32 TypeConvert::ToUint32(const char* str)
{
	if (!str)
	{
		return 0;
	}
	return static_cast<uint32>(strtoul(str, NULL, 10));
}

int64 TypeConvert::ToInt64(const char* str)
{
	if (!str)
	{
		return 0;
	}
	return boost::lexical_cast<int64>(str);
}

uint64 TypeConvert::ToUint64(const char* str)
{
	if (!str)
	{
		return 0;
	}
	return boost::lexical_cast<uint64>(str);
}

float TypeConvert::ToFloat(const char* str)
{
	if (!str)
	{
		return 0;
	}
	return boost::lexical_cast<float>(str);
}

double TypeConvert::ToDouble(const char* str)
{
	if (!str)
	{
		return 0;
	}
	return boost::lexical_cast<double>(str);
}

std::string TypeConvert::ToString(int8 value)
{
	char buffer[64];
	sprintf_s(buffer, "%d", value);
	return string(buffer);
}

std::string TypeConvert::ToString(uint8 value)
{
	char buffer[64];
	sprintf_s(buffer, "%u", value);
	return string(buffer);
}

std::string TypeConvert::ToString(int16 value)
{
	char buffer[64];
	sprintf_s(buffer, "%d", value);
	return string(buffer);
}

std::string TypeConvert::ToString(uint16 value)
{
	char buffer[64];
	sprintf_s(buffer, "%u", value);
	return string(buffer);
}

std::string TypeConvert::ToString(int32 value)
{
	char buffer[64];
	sprintf_s(buffer, "%d", value);
	return string(buffer);
}

std::string TypeConvert::ToString(uint32 value)
{
	char buffer[64];
	sprintf_s(buffer, "%u", value);
	return string(buffer);
}

std::string TypeConvert::ToString(int64 value)
{
	char buffer[64];
	sprintf_s( buffer, "%lld", value );
	return string( buffer );
}

std::string TypeConvert::ToString(uint64 value)
{
	char buffer[64];
	sprintf_s( buffer, "%llu", value );
	return string( buffer );
}

std::string TypeConvert::ToString(float value)
{
	char buffer[64];
	sprintf_s( buffer, "%f", value );
	return string( buffer );
}

std::string TypeConvert::ToString(double value)
{
	char buffer[64];
	sprintf_s( buffer, "%f", value );
	return string( buffer );
}



