#include "../Include/SysUtil.h"

void SysUtil::Sleep( uint ms )
{
#if TARGET_PLATFORM == PLATFORM_WIN
	//����;
	::Sleep( ms );
#else
	//΢��;
	usleep( ms * 1000 );
#endif
}

uint SysUtil::GetMSTime()
{
#if TARGET_PLATFORM == PLATFORM_WIN
	return ::GetTickCount();
#else
	struct timeval tv;
	gettimeofday( &tv, NULL );
	return ( tv.tv_sec * 1000 ) + ( tv.tv_usec / 1000 );
#endif
}

