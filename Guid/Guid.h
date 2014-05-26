/*!
 * \file Guid.h
 *
 * \author lixiang
 * \date ���� 2014
 *
 * Guid
 */


#pragma once

#include "LeeConfig.h"
#include "PlatForm.h"

#if TARGET_PLATFORM == PLATFORM_LINUX
#include<uuid/uuid.h>
#endif


class Guid														//128bit Guid
{
public:
	struct PtrCmp											//Guidָ���ַ�Ƚ�; 
	{
		bool operator()(const Guid* left, const Guid* right) const
		{
			return *left < *right;
		}
	};

	Guid();			

	~Guid();

	Guid(const Guid& guid);

	explicit Guid(const int8* strGuid);								//��ֹ���������캯�����Զ�����ת��;

	explicit Guid(const string& strGuid);

#if TARGET_PLATFORM == PLATFORM_WINDOWS
	static void Initialize();													//��windowsƽ̨�±������������� (������ʱ��֪�� �����û���ʲô��) Init COM��;

	static void Uninitialize();											//UnInit COM��(�������Ҫ������ĳɶ�ʹ��);
#endif

	static bool CreateGuid(Guid& guid);							//����GUID;

	bool IsNull(void);														

	bool IsNull( void )const;													//�ж�GUID �Ƿ�Ϊ��(const�汾);

	bool Evaluate( const Guid& guid );											//�ж�GUID �Ƿ����;

	const int8* ToCStr( void ) const;											//�� GUID ת��ΪC���� const char* ���� ����!! �ڲ�ʹ�þ�̬�ַ������飬������sprintf()���������2�����ϵ�tostring����; ������ֻ�����ѹջ��GUID���ݣ�ǰ���GUID����������; ����ΪʲôҪʹ�þ�̬�ַ�����������BUG?�ѵ���Ϊ�˲�������ͣ�Ķ������Ч��?

	string ToStr( void ) const;												//�� GUID ת��Ϊ string ����;

	void MakeSqlString( int8** buffer );										//��GUIDת��Ϊ sql �����ַ���;(��������иĽ��Ŀռ�)

	void MakeGuid( const int8* szGuid );										//���ַ���ʽ��GUID ת��Ϊ ֵ��ʽ��GUID;

	void Make( const string &str);												//ͬ�� ������һ��;

	Guid& operator = (const Guid& guid);									//���� = ������;

	bool operator == (const Guid& guid) const;							//���� == ������;

	bool operator != (const Guid& guid) const;							//���� != ������;

	bool operator < (const Guid& guid) const;							//���� < ������;

	bool operator > (const Guid& guid) const;							//���� >  ������;

	bool CharConvertValue(const char* szValue, int32& retValue);		//���ַ�ת��Ϊʵֵ;

	static Guid GUID_INVALID;													//��Ч��GUID(ȫΪ0) ����������Guid��ĳ�ʼ��;

private:
	uint32	_Data1;
	uint16	_Data2;
	uint16	_Data3;
	uint8	_Data4[8];
};

const Guid NULL_GUID = Guid::GUID_INVALID;