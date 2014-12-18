#include "SysUtil.h"

void SysUtil::Sleep( uint32 ms )
{
#if TARGET_PLATFORM == PLATFORM_WIN
	//∫¡√Î;
	::Sleep( ms );
#else
	//Œ¢√Î;
	usleep( ms * 1000 );
#endif
}

uint32 SysUtil::GetMSTime()
{
#if TARGET_PLATFORM == PLATFORM_WINDOWS
	return ::GetTickCount();
#else
	struct timeval tv;
	gettimeofday( &tv, NULL );
	return ( tv.tv_sec * 1000 ) + ( tv.tv_usec / 1000 );
#endif
}

void SysUtil::SetConsoleColor(unsigned short ForeColor /*= FG_WHITE*/, unsigned short BackGroundColor /*= 0*/)
{
#if TARGET_PLATFORM == PLATFORM_WINDOWS
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleTextAttribute(hCon, ForeColor | BackGroundColor);

#elif TARGET_PLATFORM == PLATFORM_LINUX

#elif TARGET_PLATFORM == PLATFORM_MAC

#endif

}

void SysUtil::RestoreConsoleColor()
{
#if TARGET_PLATFORM == PLATFORM_WINDOWS
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, FG_WHITE  | 0);

#elif TARGET_PLATFORM == PLATFORM_LINUX

#elif TARGET_PLATFORM == PLATFORM_MAC

#endif
}



