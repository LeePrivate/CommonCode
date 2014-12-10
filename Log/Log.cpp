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
	cout<<"默认日志Destruction!"<<endl;
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
#if defined(_DEBUG) || defined(DEBUG)			//Linux 下是定义的 DEBUG,如果是debug模式那么在控制台也输出一次信息;
		printf("%s\n", msg);
#endif
	}

	if (_LogOpt._bAddTimestamp)
	{
		time_t ctTime;
		time(&ctTime);							//得到时间;

		struct tm stTime;
		localtime_s(&stTime, &ctTime);		//转换为tm格式时间;
	
		//char tmpTime[32];
		//asctime_s(tmpTime, &stTime);    //这个是转换为标准格式 如: Wed May 21 20:31:29 2014 ;

		//自定义格式;
		_stdOF<< stTime.tm_year + 1900 << "/"														//年 since 1900;
			<< stTime.tm_mon + 1 << "/"																		//月 0 - 11;
			<< stTime.tm_mday << " "																			//日 1 - 31;
			<< std::setw(2) <<std::setfill('0') << stTime.tm_hour										//小时;
			<< ":" << std::setw(2) <<std::setfill('0') << stTime.tm_min							//分;
			<< ":" << std::setw(2) << std::setfill('0') << stTime.tm_sec							//秒;
			<< " : ";
	}
	_stdOF << msg << endl;
	//_File.flush();   //这个不需要了, 在遇到std::endl控制字符的时候 flush 就被调用了;
}

void Log::Update()
{

}



LogMgr::LogMgr()
	:_LogReCreateInterval(7200)//重新生成日志的时间为7200秒(两小时);
{
	LogOpt logOpt;
	logOpt._sLogName = logOpt._sCreateTime;
	//替换文件名中不允许的字符;
	StringUtil::Replace(logOpt._sLogName,":", "-");
	//验证文件名;
	VerifyFileName(logOpt._sLogName);	
	//构造的时候就生成默认日志Log;( ios::app 在原有日志后面添加, ios::out 开启新的日志)
	_DefaultLog = new Log(logOpt);		
	//将默认日志加入日志管理;
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
	//判断日志生成间隔时间是否达到;
	int timeInterval = DataTimeUtil::GetTimeStampSecondTotal(_DefaultLog->_LogOpt._sCreateTime, DataTimeUtil::GetYMD_HMS_String());
	//如果时间间隔达到(释放原 _stdOF 生成新的 _stdOF);
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
		//如果这个指定的日志文件不存在,那么就创建一个;
		//由于在LogMgr类初始化的时候就已经有一个Log加入到LogMap里面作为默认日志文件纯在了;
		//所以这个指定的文件一定不会是默认日志文件,输出的时候要用SpecityLog宏
		//输出不成功的话就肯定有问题,检查!;
		//注意!!!再次寻找的文件名是 AddLog返回的文件名,应为有改变文件名的情况出现.列入,输入文件名时忘记后缀,在Add的时候就会加上;
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
