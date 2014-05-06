/*!
 * \file BoostFilesystem.h
 *
 * \author LEE
 * \date 五月 2014
 *使用说明:
 *该组件使用boost库来达到文件的查找,验证,转换文件编码等工作;
 *使用时 需要在工作目录建立Config文件夹,其中建立 XmlConvertConfig.xml 配置文件,其中给出读取文件的路径,和要保存的目的地路径;
 *
 *使用步骤:
 *BoostFileSystem::GetSingle().ReadXmlConfig();															1.从XML读取目标文件路径和文件转换目的地路径;
 *BoostFileSystem::GetSingle().SearchAndVerifyFile();													2.验证配置文件中要找的文件的路径或是文件是否存在;
 */

#pragma once

#include "LeeConfig.h"
#include "tinyxml.h"
#include <boost/filesystem.hpp>																													//Boost FileSystem header file;
#include <boost/locale/encoding.hpp>																										//Boost code conversion header file;

#if defined  _WIN32 || defined _WIN64																										//Platform define 32bit or 64bit;
#include <Windows.h>
#endif



class BoostFileSystem
{
public:
	BoostFileSystem();																									

	~BoostFileSystem();					

	bool ReadXmlConfig();																																	//读取xml配置文件;

	bool SearchAndVerifyFile();																															//验证输入的文件路径,如果是文件夹则自动寻找里面的xml文件;

	boost::filesystem::path& GetFolderOrFilename();																							//得到文件夹路径或文件路径;

	string GetDestinationPath();																															//得到文件转换目的地路径;
		
	bool IsTmxFile(boost::filesystem::path& filePath);																							//验证是否是Tmx文件;

	void ShowFilename();																																	//输出m_vecFile中的文件路径;

	bool IsHaveMatchedFile();																																//判断是否有满足要求的文件(m_vecFile 是否为空);

	vector<string>& GetFilePathVec();																												//得到所有查找出来的需转换的文件路径的vec;

	void Clear();																																					//清除类中数据;

	SINGLE_MODE(BoostFileSystem);																													//单列模式,返回引用 GetSingle();		

	SINGLE_MODE_POINTER(BoostFileSystem);																									//单列模式返回指针 GetSinglePointer();

protected:
	boost::filesystem::path		m_TargetPath;																										//目标文件夹路径或目标文件路径;

	string	m_DestinationPath;																															//转换目的地路径;

	vector<boost::filesystem::path> m_vecFilePath;																							//存放所有文件夹中文件路径的vector;

	vector<string> m_vecFile;																															//用vector<string>方式再存放一次文件路径用于后续文件读写操作;

private:
};



class BoostCodeConversion														
{
public:
	void ConvertGbkToUtf8_Boost(string& strGbk);

	void ConvertUtf8ToGbk_Boost(string& strUtf8);

#if defined _WIN32 || defined _WIN64

	void ConvertGbkToUtf8_WIN( string& strGBK );

	void ConvertUtf8ToGbk_WIN( string& strUtf8 );

#endif

	SINGLE_MODE(BoostCodeConversion);

	SINGLE_MODE_POINTER(BoostCodeConversion);
protected:
	BoostCodeConversion()
	{
	}

	~BoostCodeConversion()
	{
	}

private:
};