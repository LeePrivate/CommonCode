/********************************************************************
	created:	2014/10/23
	created:	23:10:2014   14:24
	filename: 	E:\Robot\Util\Include\SysUtil.h
	file path:	E:\Robot\Util\Include
	file base:	SysUtil
	file ext:	h
	author:		李翔;
	
	purpose:	一些与系统有关的工具函数;
*********************************************************************/
#pragma once

#include "../LeeConfig.h"

#if TARGET_PLATFORM == PLATFORM_WINDOWS
#include <winsock2.h>
#include <windows.h>
#elif TARGET_PLATFORM == PLATFORM_LINUX
#include <sys/time.h>
#elif TARGET_PLATFORM == PLATFORM_MAC
//如果是MAC平台,这里添加MAC 的时间相关头文件;
#include <macTime.h>
#endif

#if TARGET_PLATFORM == PLATFORM_WINDOWS
/*控制台色彩枚举,有其他需要请自行添加;*/
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
	/*设置休眠时间;*/
	static void Sleep(uint32 ms);

	/*得到当前系统时间(毫秒级);*/
	static uint32 GetMSTime();

	/*设置控制台 前景|背景 颜色; !!!注意 : 这个函数要和下面的配对使用, 否则色彩就一直是这次设定的这个了; */
	static void SetConsoleColor(unsigned short ForeColor = FG_WHITE, unsigned short BackGroundColor = 0);

	/*恢复控制台原来色彩;*/
	static void RestoreConsoleColor();
};



/* 设置控制台前景色,并还原 !!!注意 CONTNET 为完整的输出语句;
Example :
SCC(FG_LIGHT_RED, cout << "Hello world!" << endl)*/
#define SCC(FG, CONTENT) SysUtil::SetConsoleColor(FG); CONTENT; SysUtil::RestoreConsoleColor();

