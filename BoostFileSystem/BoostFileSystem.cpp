#include "BoostFilesystem.h"
#include "XmlConvertCsv.h"


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
		
		TiXmlElement* TargetNode = rootNode->FirstChildElement("TargetPath");			//��ȡĿ���ļ�·��;
		string tmpStr = TargetNode->Attribute("Path");
		XmlConvertCsv::GetSingle().ConvertUtf8ToGbk_Boost(tmpStr);
		m_TargetPath = tmpStr;
		
		TiXmlElement* DestNode = rootNode->FirstChildElement("SavePath");				//��ȡĿ�ĵ�·��;
		tmpStr =DestNode->Attribute("Path");
		XmlConvertCsv::GetSingle().ConvertUtf8ToGbk_Boost(tmpStr);
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
			//copy(boost::filesystem::directory_iterator(m_FolderOrFilename), boost::filesystem::directory_iterator(), ostream_iterator<boost::filesystem::directory_entry>(cout, "\n"));  //���ļ����е��ļ������ļ���·�����;
			copy(boost::filesystem::directory_iterator(m_TargetPath), boost::filesystem::directory_iterator(), back_inserter(m_vecFilePath));								//�� m_FolderOrFilename �е����ļ��к��ļ�,�ֱ��ŵ�һ��vector��;
			
			for (vector<boost::filesystem::path>::iterator iter = m_vecFilePath.begin(); iter != m_vecFilePath.end() ; ++iter)
			{
				if (boost::filesystem::is_regular_file(*iter))																														
				{
					if (IsTmxFile(*iter))																																											//�Ƿ���.xml�ļ�;
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

			if (IsTmxFile(m_TargetPath))																																						//�ҵ������������ļ�����vector;
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
	if (".tmx" == boost::filesystem::extension(filePath))																																		//�ҵ������������ļ�����vector;
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