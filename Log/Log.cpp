#include "Log.h"

Log::Log(LogOpt logOpt)
{
	_LogOpt = logOpt;
	_stdOF.open(_LogOpt._sLogName.c_str(), _LogOpt._OpenMode);
	if (!_stdOF.is_open())
	{
		assert(false);
	}
}

Log::~Log()
{
	_stdOF.close();
	cout<<"Ĭ����־Destruction!"<<endl;
}

const string& Log::GetLogName() const
{
	return _LogOpt._sLogName;
}

void Log::Write(const char* msg)
{
	if (!_stdOF.is_open())
	{
		assert(false);
		return;
	}

	if (NULL == msg)
	{
		return;
	}

	if (_LogOpt._bDebugPrint)
	{
#if defined(_DEBUG) || defined(DEBUG)			//Linux ���Ƕ���� DEBUG,�����debugģʽ��ô�ڿ���̨Ҳ���һ����Ϣ;
		printf("%s\n", msg);
#endif
	}

	if (_LogOpt._bAddTimestamp)
	{
		time_t ctTime;
		time(&ctTime);							//�õ�ʱ��;

		struct tm stTime;
		localtime_s(&stTime, &ctTime);		//ת��Ϊtm��ʽʱ��;
	
		//char tmpTime[32];
		//asctime_s(tmpTime, &stTime);    //�����ת��Ϊ��׼��ʽ ��: Wed May 21 20:31:29 2014 ;

		//�Զ����ʽ;
		_stdOF<< stTime.tm_year + 1900 << "/"														//�� since 1900;
			<< stTime.tm_mon + 1 << "/"																		//�� 0 - 11;
			<< stTime.tm_mday << " "																			//�� 1 - 31;
			<< std::setw(2) <<std::setfill('0') << stTime.tm_hour										//Сʱ;
			<< ":" << std::setw(2) <<std::setfill('0') << stTime.tm_min							//��;
			<< ":" << std::setw(2) << std::setfill('0') << stTime.tm_sec							//��;
			<< " : ";
	}
	_stdOF << msg << endl;
	//_File.flush();   //�������Ҫ��, ������std::endl�����ַ���ʱ�� flush �ͱ�������;
}

void Log::Update()
{

}



LogMgr::LogMgr()
	:_LogReCreateInterval(7200)//����������־��ʱ��Ϊ7200��(��Сʱ);
{
	LogOpt logOpt;
	logOpt._sLogName = logOpt._sCreateTime;
	//�滻�ļ����в�������ַ�;
	StringUtil::Replace(logOpt._sLogName,":", "-");
	//��֤�ļ���;
	VerifyFileName(logOpt._sLogName);	
	//�����ʱ�������Ĭ����־Log;( ios::app ��ԭ����־�������, ios::out �����µ���־)
	_DefaultLog = new Log(logOpt);		
	//��Ĭ����־������־����;
	_mapLog[logOpt._sLogName] = _DefaultLog;																
}

LogMgr::~LogMgr()
{
	for (LogMap::iterator iter = _mapLog.begin() ; iter != _mapLog.end() ; ++iter)
	{
		delete iter->second;
	}
	_mapLog.clear();
}

string LogMgr::AddLog(LogOpt logOpt)
{
	VerifyFileName(logOpt._sLogName);
	_mapLog[logOpt._sLogName] = new Log(logOpt);
	return logOpt._sLogName;
}

void LogMgr::WriteDefaultLog(const char* format, ...)
{
	if (NULL == _DefaultLog)
	{
		assert(false);
		return;
	}
	//�ж���־���ɼ��ʱ���Ƿ�ﵽ;
	int timeInterval = DataTimeUtil::GetTimeStampSecondTotal(_DefaultLog->_LogOpt._sCreateTime, DataTimeUtil::GetYMD_HMS_String());
	//���ʱ�����ﵽ(�ͷ�ԭ _stdOF �����µ� _stdOF);
	if (timeInterval>_LogReCreateInterval)
	{
		LogMap::iterator iter =  _mapLog.find(GetDefaultLogName());
		if (iter != _mapLog.end())
		{
			delete iter->second;
			_mapLog.erase(iter);
		}
		else
		{
			assert(false);
		}

		LogOpt logOpt;
		logOpt._sLogName = logOpt._sCreateTime;
		StringUtil::Replace(logOpt._sLogName,":", "-");
		VerifyFileName(logOpt._sLogName);	
		_DefaultLog = new Log(logOpt);		
		_mapLog[logOpt._sLogName] = _DefaultLog;									
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
		//������ָ������־�ļ�������,��ô�ʹ���һ��;
		//������LogMgr���ʼ����ʱ����Ѿ���һ��Log���뵽LogMap������ΪĬ����־�ļ�������;
		//�������ָ�����ļ�һ��������Ĭ����־�ļ�,�����ʱ��Ҫ��SpecityLog��
		//������ɹ��Ļ��Ϳ϶�������,���!;
		//ע��!!!�ٴ�Ѱ�ҵ��ļ����� AddLog���ص��ļ���,ӦΪ�иı��ļ������������.����,�����ļ���ʱ���Ǻ�׺,��Add��ʱ��ͻ����;
		LogOpt logOpt;
		logOpt._sLogName = fileName;
		iter = _mapLog.find(AddLog(logOpt));
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

std::string LogMgr::GetDefaultLogName()
{
	return _DefaultLog->GetLogName();
}

void LogMgr::SetLogReCreateInterval( int secTime )
{
	_LogReCreateInterval = secTime;
}
