#include "Stream.h"

BaseStream::BaseStream()
	:_eStreamError(EStreamError_OK)
{

}

BaseStream::~BaseStream()
{

}

EStreamError BaseStream::GetError() const
{
	return _eStreamError;
}

bool BaseStream::IsOK() const
{
	return EStreamError_OK == _eStreamError;
}

size_t BaseStream::GetSpace() const
{
	return GetSize() - GetOffset();
}

Stream::Stream(uint8* pBuffer, size_t size)
	:_Buffer(pBuffer)
	,_Pointer(pBuffer)
	,_Size(size)
{
	assert(_Buffer);
}

Stream::Stream(size_t size)
{
	_Size = size;
	_Buffer = new uint8[_Size];
	_Pointer = _Buffer;
}

Stream::~Stream(void)
{

}

void Stream::ReleaseBuffer()
{
	SAFE_DELETE_ARRAY(_Buffer);
	_Pointer = _Buffer;
	_Size = 0;
}

size_t Stream::GetOffset() const
{
	return (size_t)(_Pointer - _Buffer);
}

size_t Stream::GetSize() const
{
	return _Size;
}
