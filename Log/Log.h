/*!
 * \file Log.h
 *
 * \author lixiang
 * \date 五月 2014
 *
 * 日子组件:非线程安全,如果多线程对同一个日志文件进行操作,需要自己做线程安全的处理;
 */

#pragma once

#include "LeeConfig.h"

class LogOpt											//日志配置;
{
	bool		_bAddTimestamp;						//是否使用时间戳;
	bool		_bDebugPrint;							//是否是Debug模式 print;
	uint32	_CacheSize;								//缓存大小;
	uint32	_CacheTime;								//缓冲时间间隔;
};

class Log
{
public:
protected:
private:
};
