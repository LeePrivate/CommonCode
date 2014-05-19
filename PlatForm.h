/*!
 * \file PlatForm.h
 *
 * \author lixiang
 * \date 五月 2014
 *
 * 平台相关宏定义;
 */

#pragma once

#define PLATFORM_WINDOWS 1
#define PLATFORM_LINUX 2
#define PLATFORM_MAC 3


// Win
#if defined(WIN32) || defined(WIN64) || defined(_WINDOWS_)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM			PLATFORM_WINDOWS
#endif

// Linux
#if defined(LINUX)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_LINUX
#endif

// Mac
#if defined(MAC)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_MAC
#endif