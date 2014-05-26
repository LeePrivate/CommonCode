/*!
 * \file Stream.h
 *
 * \author lixiang
 * \date ���� 2014
 *
 * �������Ĳ���
 */

// ��д��ʱ��ǵü����������궨��
// 	BASESTREAM_READ( long );
// 	BASESTREAM_WRITE(unsigned long)

#pragma once

#include "Guid.h"
#include "TypeConvert.h"

//����ö��;
typedef enum
{
	EStreamError_Error,					
	EStreamError_OK,
	EStreamError_BufferFull, 
	EStreamError_BadArg,
}EStreamError;

//�������ӿ�;
class BaseStream
{
public:
	BaseStream();

	virtual ~BaseStream();

protected:
	EStreamError _eStreamError;
};