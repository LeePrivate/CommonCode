/*!
 * \file Stream.h
 *
 * \author lixiang
 * \date 五月 2014
 *
 * 数据流的操作
 */

// 在写的时候记得加上这两个宏定义
// 	BASESTREAM_READ( long );
// 	BASESTREAM_WRITE(unsigned long)

#pragma once

#include "Guid.h"
#include "TypeConvert.h"

//错误枚举;
typedef enum
{
	EStreamError_Error,					
	EStreamError_OK,
	EStreamError_BufferFull, 
	EStreamError_BadArg,
}EStreamError;

//数据流接口;
class BaseStream
{
public:
	BaseStream();

	virtual ~BaseStream();

protected:
	EStreamError _eStreamError;
};