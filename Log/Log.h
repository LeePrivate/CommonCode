/********************************************************************
	created:	2014/10/23
	created:	23:10:2014   17:13

	author:		李翔;
	
	purpose:	日志组件:非线程安全,如果多线程对同一个日志文件进行操作,需要自己做线程安全的处理;
	
	使用方法:包含头文件以后,直接在要输出日志的地方使用定义的宏,如下;
	输出到默认的日志文件 DefaultLog("%s output &d", char, int);
	注意默认日志是以Log创建时间为文件名;
	输出到指定文件名的日志(比如登录信息可以单独用一个文件来存放之类的) SpecityLog("文件名","%s output &d", char, int );
	
	注意: 每个日志文件,在Log类创建的时候就已经按照默认app方式打开了,日志输出会根据时间每两个小时另外创建一个文件来输出日志;
	
	实际工作中有其他需求再来做修改;
	以后来增加写如数据库的日志系统,根据文件大小换一个文件继续输出日志功能;
*********************************************************************/



#pragma once

#include "Config.h"
#include "DataTimeUtil.h"
#include "StringUtil.h"


//日志配置信息;
struct LogOpt											
{
	//日志文件名;
	string	_sLogName;			

	//日志创建时间;
	string	_sCreateTime;	

	//打开模式 ios::out 如果有文件就删除重建, ios::app 有文件就从后面添加;
	std::ios::openmode _OpenMode;	

	//是否使用时间戳;
	bool		_bAddTimestamp;		

	//是否是Debug模式 print;
	bool		_bDebugPrint;		

	//缓存大小(暂时没有用到);
	uint32	_CacheSize;		

	//缓冲时间间隔(暂时没有用到);
	uint32	_CacheTime;								

	LogOpt()
		:_sLogName("DefaultLog.txt")
		,_sCreateTime(DataTimeUtil::GetYMD_HMS_String())
		,_OpenMode(ios::app)
		,_bAddTimestamp(true)
		,_bDebugPrint(true)
		,_CacheSize(0)
		,_CacheTime(0)
	{
	}
};

class Log
{
public:
	Log(LogOpt logOpt);			

	virtual ~Log();

	const string& GetLogName() const;

	//写日志;
	virtual void Write(const char* msg);								

	//更新(这里面什么都木有....);
	virtual void Update();													

	//日志详细配置信息;
	LogOpt				_LogOpt;

protected:
	std::ofstream	_stdOF;												
	

//todo:增加缓冲模式,达到一定量的日志量或则一定时间间隔,才真正写入硬盘,减少硬盘IO次数(以后来写);
};



//日志管理;
class LogMgr				
{
public:
	LogMgr();

	~LogMgr();

	string AddLog(LogOpt logOpt);		//添加日志 ios::out 如果有文件就删除重建, ios::app 有文件就从后面添加 函数返回正真添加进LogMap的文件名, 应为会有改变文件名的情况;

	void WriteDefaultLog(const char* format, ...);									//记录日志到默认Log;

	void WriteSpecifyLog(string fileName, const char* format, ...);			//记录日志(指定文件,需要在之前Add一个Log 到 Log Map 中);

	bool SetDefaultLog(const string& fileName);									//设置默认日志;

	void Updata();																					//更新;

	void VerifyFileName(string& fileName);												//在加入新日志文件时验证日志文件名,如果没有加.txt,会自动加上,以防忘记写文件名后缀的情况;

	string GetDefaultLogName();															//得到默认日志的文件名;

	void SetLogReCreateInterval(int secTime);											//设置重新生成日志的时间间隔(默认是两小时,每次新运行程序都会生成新的日志);

	SINGLE_MODE(LogMgr);							

protected:
	typedef map<string, Log*>		LogMap;
	
	LogMap	_mapLog;

	Log*			_DefaultLog;

	//日志重新生成间隔时间(默认秒:7200 两小时);
	int			_LogReCreateInterval;		

	//单条日志最大长度;
	static const int s_MaxLogLen = 16 *1024;				
};

//得到日志管理类;
#define GetLogMgr LogMgr::GetSingle()		

//输出到默认日志;
#define DefaultLog(...) LogMgr::GetSingle()->WriteDefaultLog(__VA_ARGS__)

//输出到指定日志,需要给出文件名,并且在输出之前要已经Add到 Log map 中;
#define SpecifyLog(_LOG_NAME_, ...) LogMgr::GetSingle()->WriteSpecifyLog(_LOG_NAME_, __VA_ARGS__)


