#pragma once

#include "LeeConfig.h"
#include "tinyxml.h"


class BoostFileSystem
{
public:
	BoostFileSystem();																									

	~BoostFileSystem();					

	bool ReadXmlConfig();																																	//读取xml配置文件;

	boost::filesystem::path& GetFolderOrFilename();																							//得到文件夹路径或文件路径;

	string GetDestinationPath();																															//得到文件转换目的地路径;
		
	bool VerifyInputAndSearch();																														//验证输入的路径,如果是文件夹则自动寻找里面的xml文件;

	bool IsTmxFile(boost::filesystem::path& filePath);																							//验证是否是Tmx文件;

	void ShowFilename();																																	//输出m_vecFile中的文件路径;

	bool IsHaveMatchedFile();																																//判断是否有满足要求的文件(m_vecFile 是否为空);

	vector<string>& GetFilePathVec();																												//得到所有查找出来的需转换的文件路径的vec;

	void Clear();																																					//清除类中数据;

	SINGLE_MODE(BoostFileSystem);

protected:
	boost::filesystem::path		m_TargetPath;																										//目标文件夹路径或目标文件路径;

	string	m_DestinationPath;																															//转换目的地路径;

	vector<boost::filesystem::path> m_vecFilePath;																							//存放所有文件夹中文件路径的vector;

	vector<string> m_vecFile;																															//用vector<string>方式再存放一次文件路径用于后续文件读写操作;
private:
};