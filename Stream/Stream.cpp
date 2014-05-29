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

uint8* Stream::GetOffsetPointer()
{
	return _Pointer;
}

void Stream::ResetPointer()
{
	_Pointer = _Buffer;
}

void Stream::SetBuffer(uint8* pBuffer, size_t size)
{
	_Size = size;
	_Buffer = pBuffer;
	_Pointer = _Buffer;
}

bool Stream::SetData(size_t pos, const void* data, size_t size)
{
	if (pos + size > _Size)
	{
		assert(false);
		return false;
	}
	memcpy(&(_Buffer[pos]), data, size);
	return true;
}

bool Stream::Ignore(size_t size)
{
	if (GetSpace() < size)
	{
		assert(false);
		_eStreamError = EStreamError_BufferFull;
		return false;
	}
	_Pointer += size;
	return true;
}

BaseStream& Stream::BytesSerialize(const void* data, size_t size)
{
	if (GetSpace() < size)
	{
		assert(false);
		_eStreamError = EStreamError_BufferFull;
		return *this;						//ԭ������û��������Լ��ӵ�,���ֲ��Ըû���;
	}
	memcpy(_Pointer, data, size);
	_Pointer += size;
	return *this;
}

BaseStream& Stream::BytesDeserialize(void* data, size_t size)
{
	if (GetSpace() < size)				
	{
		assert(false);
		_eStreamError = EStreamError_BufferFull;//����ʵ���������ö�ٱ�ﲻ׼ȷ,Ӧ����Ҫȡ���ݵĳ���,������buffer���滹ʣ�����ݳ���,��ƥ����,�Ժ�����;
		return *this;
	}
	memcpy(data, _Pointer, size);
	_Pointer += size;
	return *this;
}

void Stream::Serialize(BaseStream& streamTo) const
{
	if (this == &streamTo)
	{
		assert(false);
		return;
	}
	streamTo << (int)GetOffset();	//int �Ϳͻ��˶�Ӧ;
	streamTo.BytesSerialize(GetBuffer(), GetOffset());	//д��streamTo ע�����ﲢ���ǽ�stream�����������һ������,���ǽ�this���е�buffer���ݷ����� ����һ�����е�buffer��;
}

void Stream::Deserialize(BaseStream& streamForm)
{
	if (this == &streamForm)
	{
		assert(false);
		_eStreamError = EStreamError_BadArg;
		return;
	}
	int dataSize = 0; //int �Ϳͻ��˶�Ӧ;
	streamForm >> dataSize;
	streamForm.BytesDeserialize(GetBuffer(), dataSize);
	//�����Ҿ��������� ,������stream ��_Point ��û�б䶯,Ӧ��Ҫ�������dataSize��,�Ժ��ִ�������;
}


StringStream::StringStream()
	:_Offset(0)
{

}

StringStream::~StringStream()
{

}

size_t StringStream::GetOffset() const
{
	return _Offset;
}

size_t StringStream::GetSize() const
{
	return _strBuffer.size();
}

string& StringStream::GetBuffer()
{
	return _strBuffer;
}

const string& StringStream::GetBuffer() const
{
	return _strBuffer;
}

void StringStream::ResetOffset()
{
	_Offset = 0;
}

bool StringStream::SetData(size_t pos, const void* data, size_t size)
{
	if (pos + size > _strBuffer.size())
	{
		assert(false);
		return false;
	}
	memcpy(&(_strBuffer[pos]), data, size);
	return true;
}

BaseStream& StringStream::BytesSerialize(const void* data, size_t size)
{
	if (NULL == data)
	{
		_eStreamError = EStreamError_BadArg;
		return *this;
	}
	_strBuffer.insert(_Offset, size, 0);
	memcpy(&(_strBuffer[_Offset]), data, size);
	_Offset += size;
	return *this;
}

BaseStream& StringStream::BytesDeserialize(void* data, size_t size)
{
	if (NULL == data)
	{
		_eStreamError = EStreamError_BadArg;
		return *this;
	}
	if (_Offset + size > _strBuffer.size())
	{
		_eStreamError = EStreamError_BufferFull;
		return *this;
	}
	memcpy(data, &(_strBuffer[_Offset]), size);
	_Offset += size;
	return *this;
}
