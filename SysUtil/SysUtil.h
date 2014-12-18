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

#include "../LeeConfig.h"

#if TARGET_PLATFORM == PLATFORM_WINDOWS
#include <winsock2.h>
#include <windows.h>
#elif TARGET_PLATFORM == PLATFORM_LINUX
#include <sys/time.h>
#elif TARGET_PLATFORM == PLATFORM_MAC
//�����MACƽ̨,�������MAC ��ʱ�����ͷ�ļ�;
#include <macTime.h>
#endif

#if TARGET_PLATFORM == PLATFORM_WINDOWS
/*����̨ɫ��ö��,��������Ҫ���������;*/
enum ConsoleColor
{
	FG_BLUE = 0x0001,
	FG_GREEN = 0x0002,
	FG_RED = 0x0004,
	FG_PURPLE = 0x0005,
	FG_YELLOW = 0x0006,
	FG_WHITE = 0x0007,
	FG_INTENSITY = 0x0008,
	FG_LIGHT_BLUE = 0x0009,
	FG_LIGHT_GREEN = 0x000A,
	FG_LIGHT_CNYA = 0x000B,
	FG_LIGHT_RED = 0x000C,

	BG_BLUE = 0x0010,
	BG_GREEN = 0x0020,
	BG_RED = 0x0040,
	BG_INTENSITY = 0x0080
};
#endif

class SysUtil
{
public:
	/*��������ʱ��;*/
	static void Sleep(uint32 ms);

	/*�õ���ǰϵͳʱ��(���뼶);*/
	static uint32 GetMSTime();

	/*���ÿ���̨ ǰ��|���� ��ɫ; !!!ע�� : �������Ҫ����������ʹ��, ����ɫ�ʾ�һֱ������趨�������; */
	static void SetConsoleColor(unsigned short ForeColor = FG_WHITE, unsigned short BackGroundColor = 0);

	/*�ָ�����̨ԭ��ɫ��;*/
	static void RestoreConsoleColor();
};



/* ���ÿ���̨ǰ��ɫ,����ԭ !!!ע�� CONTNET Ϊ������������;
Example :
SCC(FG_LIGHT_RED, cout << "Hello world!" << endl)*/
#define SCC(FG, CONTENT) SysUtil::SetConsoleColor(FG); CONTENT; SysUtil::RestoreConsoleColor();

