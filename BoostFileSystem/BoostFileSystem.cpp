#include "BoostFilesystem.h"


BoostFileSystem::BoostFileSystem()
{

}

BoostFileSystem::~BoostFileSystem()
{

}

bool BoostFileSystem::ReadXmlConfig()
{
	do 
	{
		TiXmlDocument doc;
		if (!doc.LoadFile("Config/XmlConvertConfig.xml"))
		{
			assert(false);
			break;
		}
		TiXmlElement* rootNode = doc.FirstChildElement("XmlConvertConfig");
		if (NULL == rootNode)
		{
			assert(false);
			break;
		}
		
		TiXmlElement* TargetNode = rootNode->FirstChildElement("TargetPath");			//读取目标文件路径;
		string tmpStr = TargetNode->Attribute("Path");
		BoostCodeConversion::GetSingle().ConvertUtf8ToGbk_Boost(tmpStr);
		m_TargetPath = tmpStr;
		
		TiXmlElement* DestNode = rootNode->FirstChildElement("SavePath");				//读取目的地路径;
		tmpStr =DestNode->Attribute("Path");
		BoostCodeConversion::GetSingle().ConvertUtf8ToGbk_Boost(tmpStr);
		m_DestinationPath = tmpStr;
	} while (0);
	return false;
}

boost::filesystem::path& BoostFileSystem::GetFolderOrFilename()
{
	return m_TargetPath;
}

string BoostFileSystem::GetDestinationPath()
{
	return m_DestinationPath;
}

bool BoostFileSystem::VerifyInputAndSearch()
{
	if (boost::filesystem::exists(m_TargetPath))											//does folder or file actually exist;
	{
		if (boost::filesystem::is_directory(m_TargetPath))								//is folder;
		{
			cout << "You input is folder ." << endl;
			//copy(boost::filesystem::directory_iterator(m_FolderOrFilename), boost::filesystem::directory_iterator(), ostream_iterator<boost::filesystem::directory_entry>(cout, "\n"));  //将文件夹中的文件或子文件夹路径输出;
			copy(boost::filesystem::directory_iterator(m_TargetPath), boost::filesystem::directory_iterator(), back_inserter(m_vecFilePath));								//将 m_FolderOrFilename 中的子文件夹和文件,分别存放到一个vector中;
			
			for (vector<boost::filesystem::path>::iterator iter = m_vecFilePath.begin(); iter != m_vecFilePath.end() ; ++iter)
			{
				if (boost::filesystem::is_regular_file(*iter))																														
				{
					if (IsTmxFile(*iter))																																											//是否是.xml文件;
					{
						m_vecFile.push_back(iter->generic_string());
					}
				}
			}
			ShowFilename();
		}
		else if (boost::filesystem::is_regular_file(m_TargetPath))																													//is file;
		{
			cout << "You input is filename" << endl;

			if (IsTmxFile(m_TargetPath))																																						//找到符合条件的文件存入vector;
			{
				m_vecFile.push_back(m_TargetPath.generic_string());
			}
			ShowFilename();
		}
		else
		{
			cout << "You input exists, but is neither folder path nor filename !" << endl;
		}
		return true;
	}
	cout << "You input error folder Path or filename  not exist !" << endl;
	return false;
}

bool BoostFileSystem::IsTmxFile(boost::filesystem::path& filePath)
{
	if (".tmx" == boost::filesystem::extension(filePath))																																		//找到符合条件的文件存入vector;
	{
		return true;
	}
	return false;
}

void BoostFileSystem::ShowFilename()
{
	if (m_vecFile.empty())
	{
		cout << "There is no matched file found !" << endl;
		return;
	}
	
	for (vector<string>::iterator iter = m_vecFile.begin() ; iter != m_vecFile.end() ; ++iter)
	{
		cout << *iter << endl;
	}
}

vector<string>& BoostFileSystem::GetFilePathVec()
{
	return m_vecFile;
}

bool BoostFileSystem::IsHaveMatchedFile()
{
	if (m_vecFile.empty())
	{
		return false;
	}
	return true;
}

void BoostFileSystem::Clear()
{
	m_TargetPath.clear();
	m_vecFile.clear();
	m_vecFilePath.clear();
}

void BoostCodeConversion::ConvertGbkToUtf8_Boost(string& strGbk)
{
	strGbk = boost::locale::conv::between(strGbk,"UTF-8", "GBK");
}

void BoostCodeConversion::ConvertUtf8ToGbk_Boost(string& strUtf8)
{
	strUtf8 = boost::locale::conv::between(strUtf8,"GBK", "UTF-8");
}

#if defined _WIN32 || defined _WIN64

void BoostCodeConversion::ConvertGbkToUtf8_WIN( string& strGBK )																					
{
	int len=MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK.c_str(), -1, NULL,0);
	WCHAR * wszUtf8 = new WCHAR[len+1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK.c_str(), -1, wszUtf8, len);

	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8=new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL,NULL);

	strGBK = szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;
}

void BoostCodeConversion::ConvertUtf8ToGbk_WIN( string& strUtf8 )																						
{
	int len=MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)(strUtf8.c_str()), -1, NULL,0);
	WCHAR * wszGBK = new WCHAR[len+1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)(strUtf8.c_str()), -1, wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK=new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, szGBK, len, NULL,NULL);

	strUtf8 = szGBK;
	delete[] szGBK;
	delete[] wszGBK;
}

#endif