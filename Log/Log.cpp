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
#if defined(_DEBUG) || defined(DEBUG)			//Linux 下是定义的 DEBUG,如果是debug模式那么在控制台也输出一次信息;
		printf("%s\n", msg);
#endif
	}

	if (_bAddTimestamp)
	{
		time_t ctTime;
		time(&ctTime);							//得到时间;

		struct tm stTime;
		localtime_s(&stTime, &ctTime);		//转换为tm格式时间;
	
		//char tmpTime[32];
		//asctime_s(tmpTime, &stTime);    //这个是转换为标准格式 如: Wed May 21 20:31:29 2014 ;

		//自定义格式
		_File<< stTime.tm_year + 1900 << "/"																//年 since 1900
			<< stTime.tm_mon + 1 << "/"																		//月 0 - 11
			<< stTime.tm_mday << " "																			//日 1 - 31
			<< std::setw(2) <<std::setfill('0') << stTime.tm_hour										//小时
			<< ":" << std::setw(2) <<std::setfill('0') << stTime.tm_min							//分
			<< ":" << std::setw(2) << std::setfill('0') << stTime.tm_sec							//秒
			<< " : ";
	}
	_File << msg << endl;
	//_File.flush();   //这个不需要了, 在遇到std::endl控制字符的时候 flush 就被调用了;
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
// // 	if (_mapLog.size() == 1)						//LogMgr 初始化的时候就会add一个log作为默认的,这里就不需要再判断了;
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
		//如果这个指定的日志文件不存在,那么就创建一个,
		//由于在LogMgr类初始化的时候就已经有一个Log加入到LogMap里面作为默认日志文件纯在了
		//所以这个指定的文件一定不会是默认日志文件,输出的时候要用SpecityLog宏
		//输出不成功的话就肯定有问题,检查!;
		//注意!!!再次寻找的文件名是 AddLog返回的文件名,应为有改变文件名的情况出现.列入,输入文件名时忘记后缀,在Add的时候就会加上;
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
