/********************************************************************
	created:	2014/10/23
	created:	23:10:2014   14:24
	filename: 	E:\Robot\Util\Include\SysUtil.h
	file path:	E:\Robot\Util\Include
	file base:	SysUtil
	file ext:	h
	author:		����;
	
	purpose:	һЩ��ϵͳ�йصĹ��ߺ���;
*********************************************************************/
#pragma once

#include "UtilConfig.h"

#if TARGET_PLATFORM == PLATFORM_WIN
#include <winsock2.h>
#include <windows.h>
#elif TARGET_PLATFORM == PLATFORM_LINUX
#include <sys/time.h>
#elif TARGET_PLATFORM == PLATFORM_MAC
//�����MACƽ̨,�������MAC ��ʱ�����ͷ�ļ�;
#include <macTime.h>
#endif

class Util_EXPORTS SysUtil
{
public:
	static void Sleep( uint ms );

	static uint GetMSTime();
};
