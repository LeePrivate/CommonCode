#include "Log.h"

Log::Log(const string& FileName, std::ios::openmode OpenMode /*= ios::app*/, bool AddTimestamp /*= true*/, bool DebugPrint /*= true*/)
{
	_FileName = FileName;
#ifdef WIN32
	_File.open(_FileName.c_str(), OpenMode);
#else
	_File.open(_FileName.c_str(), OpenMode);
#endif
	_bAddTimestamp = AddTimestamp;
	_bDebugPrint = DebugPrint;
}

Log::~Log()
{
	_File.close();
}

const string& Log::GetFileName() const
{
	return _FileName;
}

void Log::Write(const char* msg)
{
	if (!_File.is_open())
	{
		assert(false);
		return;
	}

	if (NULL == msg)
	{
		return;
	}

	if (_bDebugPrint)
	{
#if defined(_DEBUG) || defined(DEBUG)			//Linux ���Ƕ���� DEBUG,�����debugģʽ��ô�ڿ���̨Ҳ���һ����Ϣ;
		printf("%s\n", msg);
#endif
	}

	if (_bAddTimestamp)
	{
		time_t ctTime;
		time(&ctTime);							//�õ�ʱ��;

		struct tm stTime;
		localtime_s(&stTime, &ctTime);		//ת��Ϊtm��ʽʱ��;
	
		//char tmpTime[32];
		//asctime_s(tmpTime, &stTime);    //�����ת��Ϊ��׼��ʽ ��: Wed May 21 20:31:29 2014 ;

		//�Զ����ʽ
		_File<< stTime.tm_year + 1900 << "/"																//�� since 1900
			<< stTime.tm_mon + 1 << "/"																		//�� 0 - 11
			<< stTime.tm_mday << " "																			//�� 1 - 31
			<< std::setw(2) <<std::setfill('0') << stTime.tm_hour										//Сʱ
			<< ":" << std::setw(2) <<std::setfill('0') << stTime.tm_min							//��
			<< ":" << std::setw(2) << std::setfill('0') << stTime.tm_sec							//��
			<< " : ";
	}
	_File << msg << endl;
	//_File.flush();   //�������Ҫ��, ������std::endl�����ַ���ʱ�� flush �ͱ�������;
}

void Log::Update()
{

}



LogMgr::LogMgr()
{
	_DefaultLog = NULL;
	AddLog("DefaultLog.txt");
}

LogMgr::~LogMgr()
{
	for (LogMap::iterator iter = _mapLog.begin() ; iter != _mapLog.end() ; ++iter)
	{
		delete iter->second;
	}
	_mapLog.clear();
}

string LogMgr::AddLog(string fileName, std::ios::openmode openMode /*= ios::app*/, bool addTimestamp /*= true*/, bool debugPrint /*= true*/)
{
	VerifyFileName(fileName);
	_mapLog[fileName] = new Log(fileName, openMode, addTimestamp, debugPrint);
	if (_mapLog.size() == 1)
	{
		_DefaultLog = _mapLog[fileName];
	}
	return fileName;
}

// void LogMgr::AddLog(Log* log)
// {
// 	if (NULL == log)
// 	{
// 		assert(false);
// 		return;
// 	}
// 	_mapLog[log->GetFileName()] = log;
// // 	if (_mapLog.size() == 1)						//LogMgr ��ʼ����ʱ��ͻ�addһ��log��ΪĬ�ϵ�,����Ͳ���Ҫ���ж���;
// // 	{
// // 		_DefaultLog = log;
// // 	}
// }

void LogMgr::WriteDefaultLog(const char* format, ...)
{
	if (NULL == _DefaultLog)
	{
		assert(false);
		return;
	}
	
	char msgBuf[s_MaxLogLen] = {'\0'};

	va_list args;
	va_start(args, format);
	vsprintf_s(msgBuf, format, args);
	va_end(args);

	_DefaultLog->Write(msgBuf);
}

void LogMgr::WriteSpecifyLog(string fileName, const char* format, ...)
{
	LogMap::iterator iter = _mapLog.find(fileName);
	while (iter == _mapLog.end())
	{
		//������ָ������־�ļ�������,��ô�ʹ���һ��,
		//������LogMgr���ʼ����ʱ����Ѿ���һ��Log���뵽LogMap������ΪĬ����־�ļ�������
		//�������ָ�����ļ�һ��������Ĭ����־�ļ�,�����ʱ��Ҫ��SpecityLog��
		//������ɹ��Ļ��Ϳ϶�������,���!;
		//ע��!!!�ٴ�Ѱ�ҵ��ļ����� AddLog���ص��ļ���,ӦΪ�иı��ļ������������.����,�����ļ���ʱ���Ǻ�׺,��Add��ʱ��ͻ����;
		iter = _mapLog.find(AddLog(fileName));
	}

	char msgBuf[s_MaxLogLen] = {'\0'};

	va_list args;
	va_start(args, format);
	vsprintf_s(msgBuf, format, args);
	va_end(args);

	iter->second->Write(msgBuf);
}

bool LogMgr::SetDefaultLog(const string& fileName)
{
	LogMap::iterator iter = _mapLog.find(fileName);
	if (iter == _mapLog.end())
	{
		return false;
	}
	_DefaultLog = iter->second;
	return true;
}

void LogMgr::Updata()
{
	for (LogMap::iterator iter = _mapLog.begin() ; iter != _mapLog.end() ; ++iter)
	{
		iter->second->Update();
	}
}

void LogMgr::VerifyFileName(string& fileName)
{
	size_t tmpPos = fileName.find(".txt");
	if (tmpPos == fileName.npos)
	{
		fileName += ".txt";
	}
}
