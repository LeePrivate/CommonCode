/********************************************************************
	created:	2014/10/23
	created:	23:10:2014   14:40
	filename: 	E:\Robot\Util\Include\DataTimeUtil.h
	file path:	E:\Robot\Util\Include
	file base:	DataTimeUtil
	file ext:	h
	author:		李翔;
	
	purpose:	与日期相关的函数;
*********************************************************************/

#pragma once

#include "LeeConfig.h"
#include <boost/date_time/posix_time/posix_time.hpp>



class DateTimeUtil
{
public:
	DateTimeUtil()
	{

	}

	~DateTimeUtil()
	{

	}

public:
	//YYYY-MM-DD-HH:MM:SS
	static string GetYMD_HMS_String();

	static int GetNowTime();

	//还原成ptime的字符串形式;
	static void RestorePTimeString( string &source );

	//还原成time_t
	static int RestoreTimeT( string& currTimeStr );

	//还原成YYYY-MM-DD-HH:MM:SS;
	static string RestoreYMD_HMS_String( int time );

	//获取时间戳(总秒数);
	static int GetTimeStampSecondTotal( string &lastTimeStr, string& currTimeStr );
	static int GetTimeStampSecondTotal( boost::posix_time::ptime lastTime, string& currTimeStr );
	static int GetTimeStampSecondTotal( string &lastTimeStr, boost::posix_time::ptime currTime );
	static int GetTimeStampSecondTotal( boost::posix_time::ptime lastTime, boost::posix_time::ptime currTime );
	static int GetTimeStampSecondTotal( int lastTime );

	static string GetStandardDataCompare();

	static void ReplaceTimeSign( string& timeString );
};
