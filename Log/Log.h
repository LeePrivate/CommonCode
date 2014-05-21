/*!
 * \file Log.h
 *
 * \author lixiang
 * \date 五月 2014
 *
 * 日子组件:非线程安全,如果多线程对同一个日志文件进行操作,需要自己做线程安全的处理;
 *
 *使用方法:包含头文件以后,直接在要输出日志的地方使用定义的宏,如下
 *输出到默认的日志文件 DefaultLog("%s output &d", char, int);
 *输出到指定文件名的日志(比如登录信息可以单独用一个文件来存放之类的) SpecityLog("文件名","%s output &d", char, int );
 *
 *注意: 每个日志文件,在Log类创建的时候就已经按照默认app方式打开了;
 */

#pragma once

#include "LeeConfig.h"

class LogOpt											//日志配置(现在这个完全没用到);
{
	bool		_bAddTimestamp;						//是否使用时间戳;
	bool		_bDebugPrint;							//是否是Debug模式 print;
	uint32	_CacheSize;								//缓存大小;
	uint32	_CacheTime;								//缓冲时间间隔;
};

class Log
{
public:
	Log(const string& FileName, std::ios::openmode OpenMode = ios::app, bool AddTimestamp = true, bool DebugPrint = true);		//ios::out 如果有文件就删除重建, ios::app 有文件就从后面添加;

	virtual ~Log();

	const string& GetFileName() const;

	virtual void Write(const char* msg);								//写日志;

	virtual void Update();													//更新(这里面什么都木有....);

protected:
	std::ofstream _File;
	string	_FileName;					//日志文件名;
	bool		_bAddTimestamp;			//是否使用时间戳;
	bool		_bDebugPrint;				//是否是Debug模式 print;

//todo:增加缓冲模式,达到一定量的日志量或则一定时间间隔,才真正写入硬盘,减少硬盘IO次数(以后来写);
};

class LogMgr												//日志管理
{
public:
	LogMgr();

	~LogMgr();

	//void AddLog(Log* log);								//添加日志(去掉这种添加日志的方式使用最简便最人性化的方式,统一方式);

	string AddLog(string fileName, std::ios::openmode openMode = ios::app, bool addTimestamp = true, bool debugPrint = true);		//添加日志 ios::out 如果有文件就删除重建, ios::app 有文件就从后面添加 函数返回正真添加进LogMap的文件名, 应为会有改变文件名的情况;

	void WriteDefaultLog(const char* format, ...);			//记录日志到默认Log;

	void WriteSpecifyLog(string fileName, const char* format, ...);			//记录日志(指定文件,需要在之前Add一个Log 到 Log Map 中);

	bool SetDefaultLog(const string& fileName);			//设置默认日志;

	void Updata();		//更新;

	void VerifyFileName(string& fileName);						//在加入新日志文件时验证日志文件名,如果没有加.txt,会自动加上,以防忘记写文件名后缀的情况;

	SINGLE_MODE(LogMgr);							

protected:
	typedef map<string, Log*>		LogMap;
	
	LogMap	_mapLog;
	Log*			_DefaultLog;

	static const int s_MaxLogLen = 16 *1024;				//单条日志最大长度;
};

//输出到默认日志;
#define DefaultLog(...) LogMgr::GetSingle().WriteDefaultLog(__VA_ARGS__)

//输出到指定日志,需要给出文件名,并且在输出之前要已经Add到 Log map 中;
#define SpecifyLog(_LOG_NAME_, ...) LogMgr::GetSingle().WriteSpecifyLog(_LOG_NAME_, __VA_ARGS__)


