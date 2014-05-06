/*!
 * \file BoostFilesystem.h
 *
 * \author LEE
 * \date ���� 2014
 *ʹ��˵��:
 *�����ʹ��boost�����ﵽ�ļ��Ĳ���,��֤,ת���ļ�����ȹ���;
 *ʹ��ʱ ��Ҫ�ڹ���Ŀ¼����Config�ļ���,���н��� XmlConvertConfig.xml �����ļ�,���и�����ȡ�ļ���·��,��Ҫ�����Ŀ�ĵ�·��;
 *
 *ʹ�ò���:
 *BoostFileSystem::GetSingle().ReadXmlConfig();															1.��XML��ȡĿ���ļ�·�����ļ�ת��Ŀ�ĵ�·��;
 *BoostFileSystem::GetSingle().SearchAndVerifyFile();													2.��֤�����ļ���Ҫ�ҵ��ļ���·�������ļ��Ƿ����;
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

	bool ReadXmlConfig();																																	//��ȡxml�����ļ�;

	bool SearchAndVerifyFile();																															//��֤������ļ�·��,������ļ������Զ�Ѱ�������xml�ļ�;

	boost::filesystem::path& GetFolderOrFilename();																							//�õ��ļ���·�����ļ�·��;

	string GetDestinationPath();																															//�õ��ļ�ת��Ŀ�ĵ�·��;
		
	bool IsTmxFile(boost::filesystem::path& filePath);																							//��֤�Ƿ���Tmx�ļ�;

	void ShowFilename();																																	//���m_vecFile�е��ļ�·��;

	bool IsHaveMatchedFile();																																//�ж��Ƿ�������Ҫ����ļ�(m_vecFile �Ƿ�Ϊ��);

	vector<string>& GetFilePathVec();																												//�õ����в��ҳ�������ת�����ļ�·����vec;

	void Clear();																																					//�����������;

	SINGLE_MODE(BoostFileSystem);																													//����ģʽ,�������� GetSingle();		

	SINGLE_MODE_POINTER(BoostFileSystem);																									//����ģʽ����ָ�� GetSinglePointer();

protected:
	boost::filesystem::path		m_TargetPath;																										//Ŀ���ļ���·����Ŀ���ļ�·��;

	string	m_DestinationPath;																															//ת��Ŀ�ĵ�·��;

	vector<boost::filesystem::path> m_vecFilePath;																							//��������ļ������ļ�·����vector;

	vector<string> m_vecFile;																															//��vector<string>��ʽ�ٴ��һ���ļ�·�����ں����ļ���д����;

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