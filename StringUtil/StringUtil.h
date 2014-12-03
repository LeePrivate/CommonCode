/********************************************************************
	created:	2014/10/23
	created:	23:10:2014   14:31
	filename: 	E:\Robot\Util\Include\StringUtil.h
	file path:	E:\Robot\Util\Include
	file base:	StringUtil
	file ext:	h
	author:		����;
	
	purpose:	�ַ�����ز�������;
*********************************************************************/
#pragma once

#include "LeeConfig.h"
#include <boost/algorithm/string.hpp>



typedef vector<string> StringVec;

class StringUtil
{
public:
	typedef std::stringstream StrStreamType;

	//ȥ���ַ����������ߵĿո�,�س�;
	static void Trim( string& str, bool left = true, bool right = true );

	//�ָ��ַ���;
	static std::vector<string> Split( const string& str, const string& delims = "\t\n", unsigned int maxSplits = 0 );

	//תСд;
	static void ToLowerCase( string& str );

	//ת��д;
	static void ToUpperCase( string& str );

	//�ַ�����ƥ��;
	static bool StartsWith( const string& str, const string& pattern, bool lowerCase = true );

	//�ַ���βƥ��;
	static bool EndWith( const string& str, const string& pattern, bool lowerCase = true );

	//��·���е�\\�滻Ϊ/;
	static string StandardisePath( const string& init );

	//�ֽ������·���е��ļ�����·��;
	static void SplitFileName( const string& qualifiedName, string& outBaseName, string& outPath );

	//ƥ��;
	static bool Match( const string& str, const string& pattern, bool caseSensitive = true );

	//�滻;
	static void Replace( string& str, const string& oldStr, const string& newStr );

	//�滻����;
	static void ReplaceSingle(string& str, const string& oldStr, const string& newStr);

	//��ȫ��������, ȷ������Խ��;
	static void StrCopy( char* dst, const char* str, int dstSize );

	//����ת��;
	static bool CodeConvert( const char* fromCharSet, const char* toCharSet, char* inBuf, size_t inLen, char* outBuf, size_t outLen );

	
	//ȥ���ַ�����ָ�����ַ�,ע��ֻ����һ���ַ�;
	static void StringOffSpecial(string& srcStr,  char c);

	//ȥ���ַ�����ͷ���β�����ַ� (srcString ԭ�ַ���, IsFront true Ϊ��ǰ��ȥ��Len��,false Ϊ�Ӻ���ȥ��len��);
	static void StringOff(string& srcString, bool IsFront, char len);

	//��ԭ�ַ�����ͷȥ���������ַ�֮ǰ���ַ���;
	static void StringUtil::StringOff( string& srcStr, string off);

	//ȥ���ַ�����ͷ���β�����ַ�(����������������Ľ�����ذ汾);
	static string StringOffRet(string& srcString, bool IsFront, char len);


	//stringת��Ϊ����(atoi);
	static int Atoi(string& srcString);

	//stringת��Ϊ����(atof);
	static double Atof(string& srcStr);

	//����ת��Ϊstring(itoa);
	static string Itoa(int& num);


	//����ַ����Ƿ���sql�ؼ���,��ֹsqlע��;
	static bool IsContainSqlSpecialChar( const string& str );


	//�ӿ�ʼ��ȡ�ַ���,��ĳ���ض��ַ�Ϊֹ,�����ض�ȡ�Ĳ���,������ to �ַ�,ԭ�ַ�������;
	static string ReadToFront(const string& srcStr, const string to);

	//�ӿ�ʼ��ȡ�ַ���,��ĳ���ض��ַ�Ϊֹ,�����ظ��ַ�����Ĳ���, ���� to �ַ�ԭ�ַ�����;
	static string ReadToBack(const string& srcStr, const string to);

	//�ӿ�ʼ��ȡ�ַ���,��ĳ���ض��ַ�Ϊֹ,�����ض�ȡ�Ĳ���,������ to �ַ�,ԭ�ַ���ɾ���Ѷ�ȡ����;
	static string ReadToFrontOff(string& srcStr, const string to);

};

