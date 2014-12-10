#include "DataTimeUtil.h"


string DateTimeUtil::GetYMD_HMS_String()
{
	string timeString = boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time());  
	ReplaceTimeSign( timeString );
	return timeString;
}

void DateTimeUtil::RestorePTimeString( string &source )
{
	string::iterator stringItr = source.begin();
	for( ; stringItr != source.end(); )
	{
		if( (*stringItr) == '-' || (*stringItr) == ':' )
			stringItr = source.erase( stringItr );
		else
			++stringItr;
	}
	source.replace(8,0,std::string("T"));
}

int DateTimeUtil::GetTimeStampSecondTotal( string &lastTimeStr, string& currTimeStr )
{
	RestorePTimeString( lastTimeStr );
	RestorePTimeString( currTimeStr );
	boost::posix_time::ptime lastTime =  boost::posix_time::from_iso_string( lastTimeStr );
	boost::posix_time::ptime currTime =  boost::posix_time::from_iso_string( currTimeStr );
	int interval = ( currTime - lastTime ).total_seconds();
	//转换格式计算完以后要重新ReplaceTimeSign,否则下次在调用这个函数的时候就会出错;
	ReplaceTimeSign(lastTimeStr);
	ReplaceTimeSign(currTimeStr);
	return interval;
}

int DateTimeUtil::GetTimeStampSecondTotal( boost::posix_time::ptime lastTime, string& currTimeStr )
{
	RestorePTimeString( currTimeStr );
	boost::posix_time::ptime currTime =  boost::posix_time::from_iso_string( currTimeStr );
	return ( currTime - lastTime ).total_seconds();
}

int DateTimeUtil::GetTimeStampSecondTotal( string &lastTimeStr, boost::posix_time::ptime currTime )
{
	RestorePTimeString( lastTimeStr );
	boost::posix_time::ptime lastTime =  boost::posix_time::from_iso_string( lastTimeStr );
	return ( currTime - lastTime ).total_seconds();
}

int DateTimeUtil::GetTimeStampSecondTotal( boost::posix_time::ptime lastTime, boost::posix_time::ptime currTime )
{
	return ( currTime - lastTime ).total_seconds();
}

int DateTimeUtil::GetTimeStampSecondTotal( int lastTime )
{
	return (int)time(NULL) - lastTime;
}

string DateTimeUtil::GetStandardDataCompare()
{
	return "YYYY-MM-DD-HH:MM:SS";
}

int DateTimeUtil::RestoreTimeT(string& currTimeStr )
{
	if( currTimeStr == DateTimeUtil::GetStandardDataCompare() )
		return 0;
	RestorePTimeString( currTimeStr );
	boost::posix_time::ptime currTime = boost::posix_time::from_iso_string( currTimeStr );
	tm tmTime = to_tm( currTime );
	time_t timeT = mktime( &tmTime );
	return (int)timeT;
}

std::string DateTimeUtil::RestoreYMD_HMS_String(int time)
{
	if( time == 0 )
		return DateTimeUtil::GetStandardDataCompare();
	time_t timeT = time;
	struct tm* t = NULL;
	localtime_s(t, &timeT );
	boost::posix_time::ptime pTime = boost::posix_time::ptime_from_tm( *t );
	string timeString = boost::posix_time::to_iso_string( pTime );
	ReplaceTimeSign( timeString );
	return timeString;
}

int DateTimeUtil::GetNowTime()
{
	time_t timeT = time(NULL);
	struct tm* t = NULL;
	localtime_s(t,  &timeT );
	timeT = mktime( t );
	return (int)timeT;
}

void DateTimeUtil::ReplaceTimeSign(string& timeString)
{
	uint32 pos = 0;
	timeString.replace(pos + 4,0,std::string("-"));
	timeString.replace(pos + 7,0,std::string("-"));

	pos = timeString.find('T');
	timeString.replace(pos,1,std::string("-"));
	timeString.replace(pos + 3,0,std::string(":"));
	timeString.replace(pos + 6,0,std::string(":"));
}

