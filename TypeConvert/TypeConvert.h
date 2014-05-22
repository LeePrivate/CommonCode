/*!
 * \file TypeConvert.h
 *
 * \author lixiang
 * \date 五月 2014
 *
 * 各种类型转换(等有空了来写成模版)
 */

#pragma once

#include "LeeConfig.h"

class TypeConvert
{
public:
	static int8 ToInt8( const char* str );
	static uint8 ToUint8( const char* str );

	static int16 ToInt16( const char* str );
	static uint16 ToUint16( const char* str );

	static int32 ToInt32( const char* str );
	static uint32 ToUint32( const char* str );

	static int64 ToInt64( const char* str );
	static uint64 ToUint64( const char* str );

	static float ToFloat( const char* str );

	static double ToDouble( const char* str );

	static string ToString( int8 value );
	static string ToString( uint8 value );

	static string ToString( int16 value );
	static string ToString( uint16 value );

	static string ToString( int32 value );
	static string ToString( uint32 value );

	static string ToString( int64 value );
	static string ToString( uint64 value );

	static string ToString( float value );

	static string ToString( double value );
};