/********************************************************************
	created:	2014/10/23
	created:	23:10:2014   14:31
	filename: 	E:\Robot\Util\Include\StringUtil.h
	file path:	E:\Robot\Util\Include
	file base:	StringUtil
	file ext:	h
	author:		李翔;
	
	purpose:	字符串相关操作函数;
*********************************************************************/
#pragma once

#include "LeeConfig.h"
#include <boost/algorithm/string.hpp>



typedef vector<string> StringVec;

class StringUtil
{
public:
	typedef std::stringstream StrStreamType;

	//去除字符串左右两边的空格,回车;
	static void Trim( string& str, bool left = true, bool right = true );

	//分割字符串;
	static std::vector<string> Split( const string& str, const string& delims = "\t\n", unsigned int maxSplits = 0 );

	//转小写;
	static void ToLowerCase( string& str );

	//转大写;
	static void ToUpperCase( string& str );

	//字符串首匹配;
	static bool StartsWith( const string& str, const string& pattern, bool lowerCase = true );

	//字符串尾匹配;
	static bool EndWith( const string& str, const string& pattern, bool lowerCase = true );

	//把路径中的\\替换为/;
	static string StandardisePath( const string& init );

	//分解出绝对路径中的文件名和路径;
	static void SplitFileName( const string& qualifiedName, string& outBaseName, string& outPath );

	//匹配;
	static bool Match( const string& str, const string& pattern, bool caseSensitive = true );

	//替换;
	static void Replace( string& str, const string& oldStr, const string& newStr );

	//替换单个;
	static void ReplaceSingle(string& str, const string& oldStr, const string& newStr);

	//安全拷贝函数, 确保不会越界;
	static void StrCopy( char* dst, const char* str, int dstSize );

	//编码转换;
	static bool CodeConvert( const char* fromCharSet, const char* toCharSet, char* inBuf, size_t inLen, char* outBuf, size_t outLen );

	
	//去除字符串中指定的字符,注意只能是一个字符;
	static void StringOffSpecial(string& srcStr,  char c);

	//去除字符串开头或结尾几个字符 (srcString 原字符串, IsFront true 为从前面去除Len个,false 为从后面去除len个);
	static void StringOff(string& srcString, bool IsFront, char len);

	//从原字符串开头去除给出的字符之前的字符串;
	static void StringUtil::StringOff( string& srcStr, string off);

	//去除字符串开头或结尾几个字符(就是上面这个函数的结果返回版本);
	static string StringOffRet(string& srcString, bool IsFront, char len);


	//string转换为数字(atoi);
	static int Atoi(string& srcString);

	//string转换为数字(atof);
	static double Atof(string& srcStr);

	//数字转换为string(itoa);
	static string Itoa(int& num);


	//检查字符串是否含有sql关键字,防止sql注入;
	static bool IsContainSqlSpecialChar( const string& str );


	//从开始读取字符串,到某个特定字符为止,并返回读取的部分,不包括 to 字符,原字符串不变;
	static string ReadToFront(const string& srcStr, const string to);

	//从开始读取字符串,到某个特定字符为止,并返回该字符后面的部分, 包括 to 字符原字符不变;
	static string ReadToBack(const string& srcStr, const string to);

	//从开始读取字符串,到某个特定字符为止,并返回读取的部分,不包括 to 字符,原字符串删除已读取部分;
	static string ReadToFrontOff(string& srcStr, const string to);

};

