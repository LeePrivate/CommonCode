#pragma once

#include "LeeConfig.h"
#include "tinyxml.h"


class BoostFileSystem
{
public:
	BoostFileSystem();																									

	~BoostFileSystem();					

	bool ReadXmlConfig();																																	//��ȡxml�����ļ�;

	boost::filesystem::path& GetFolderOrFilename();																							//�õ��ļ���·�����ļ�·��;

	string GetDestinationPath();																															//�õ��ļ�ת��Ŀ�ĵ�·��;
		
	bool VerifyInputAndSearch();																														//��֤�����·��,������ļ������Զ�Ѱ�������xml�ļ�;

	bool IsTmxFile(boost::filesystem::path& filePath);																							//��֤�Ƿ���Tmx�ļ�;

	void ShowFilename();																																	//���m_vecFile�е��ļ�·��;

	bool IsHaveMatchedFile();																																//�ж��Ƿ�������Ҫ����ļ�(m_vecFile �Ƿ�Ϊ��);

	vector<string>& GetFilePathVec();																												//�õ����в��ҳ�������ת�����ļ�·����vec;

	void Clear();																																					//�����������;

	SINGLE_MODE(BoostFileSystem);

protected:
	boost::filesystem::path		m_TargetPath;																										//Ŀ���ļ���·����Ŀ���ļ�·��;

	string	m_DestinationPath;																															//ת��Ŀ�ĵ�·��;

	vector<boost::filesystem::path> m_vecFilePath;																							//��������ļ������ļ�·����vector;

	vector<string> m_vecFile;																															//��vector<string>��ʽ�ٴ��һ���ļ�·�����ں����ļ���д����;
private:
};