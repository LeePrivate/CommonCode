#include "Log.h"

Log::Log(const string& FileName, std::ios::openmode OpenMode /*= ios::out*/, bool AddTimestamp /*= true*/, bool DebugPrint /*= true*/)
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
#if defined(_DEBUG) || defined(DEBUG)			//Linux 下是定义的 DEBUG;
		printf("%s\n", msg);
#endif
	}

	if (_bAddTimestamp)
	{
		struct tm* pTime = NULL;
		time_t ctTime;
		time(&ctTime);							//得到时间;
		localtime_s(pTime, &ctTime);		//转换为tm格式时间;
		if (pTime)
		{
			_File << std::setw(2) <<std::setfill('0') << pTime->tm_hour
				<< ":" << std::setw(2) <<std::setfill('0') << pTime->tm_min
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
				<< ":";
		}
	}
	_File << msg << std::endl;
	//_File.flush();   //这个不需要了, 在遇到std::endl控制字符的时候 flush 就被调用了;
}

void Log::Update()
{

}



LogMgr::LogMgr()
{
	_DefaultLog = NULL;
	AddLog("Log");
}

LogMgr::~LogMgr()
{
	for (LogMap::iterator iter = _mapLog.begin() ; iter != _mapLog.end() ; ++iter)
	{
		delete iter->second;
	}
	_mapLog.clear();
}

void LogMgr::AddLog(const string& fileName, std::ios::openmode openMode /*= ios::out*/, bool addTimestamp /*= true*/, bool debugPrint /*= true*/)
{
	_mapLog[fileName] = new Log(fileName, openMode, addTimestamp, debugPrint);
	if (_mapLog.size() == 1)
	{
		_DefaultLog = _mapLog[fileName];
	}
}

void LogMgr::AddLog(Log* log)
{
	if (NULL == log)
	{
		assert(false);
		return;
	}
	_mapLog[log->GetFileName()] = log;
// 	if (_mapLog.size() == 1)						//LogMgr 初始化的时候就会add一个log作为默认的,这里就不需要再判断了;
// 	{
// 		_DefaultLog = log;
// 	}
}

void LogMgr::WriteLog(const string& fileName, const char* format, ...)
{
	LogMap::iterator iter = _mapLog.find(fileName);
	if (iter == _mapLog.end())
	{
		assert(false);
		return;
	}
	char msgBuf[s_MaxLogLen] = {'\0'};

	va_list args;
	va_start(args, format);
	vsprintf_s(msgBuf, format, args);
	va_end(args);

	iter->second->Write(msgBuf);
}

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
