#pragma once

#include <assert.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <time.h>
#include <stdarg.h>							//va_list va_start ..ʹ��;
#include <algorithm>
#include <functional>




using namespace std;

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long long uint64;
typedef long long int64;

//单例模式,更准�?
#define SINGLE_MODE( ClassName ) \
	static ClassName& GetSingle() \
{ \
	static ClassName s_##ClassName; \
	return s_##ClassName; \
}

#define SINGLE_MODE_POINTER( ClassName ) \
	static ClassName* GetSinglePointer() \
{ \
	static ClassName s_##ClassName; \
	return &s_##ClassName; \
}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(varType var){ varName = var; }

#define CREATE_INSTANCE(__TYPE__) \
	static __TYPE__* Create() \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
	if (pRet) \
	{\
		return pRet; \
	}\
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
}

#define BZERO(b,len) (memset((b), 0, (len)), (void) 0)

#if !defined( SAFE_DELETE )
#define SAFE_DELETE( p ) if( ( p ) ) { delete ( p ); ( p ) = 0; }
#endif

#if !defined( SAFE_DELETE_ARRAY )
#define SAFE_DELETE_ARRAY( p ) if( ( p ) ) { delete []( p ); ( p ) = 0; }
#endif

/*----------------------------------------------------------------------------------------���� FOR_EACH ��д�궨��----------------------------------------------------------*/

/*
ע : �����ֻ����vs2010���ϵİ汾���ܱ���ͨ��, vs2010 ��֧��C++11;
ʹ��C++11��д��,ins Ϊ stl ��������� vector map �ȵĶ���ʵ��, elem Ϊ������Ԫ�ر�����(�����Զ�);
����д�����Ӽ��;
��:content Ϊ vector<string> ��ô elem Ϊÿһ��string������;
��:content Ϊ map<int, string> ��ô elem Ϊÿһ��pair��Ӧ��, elem.second ��������;
ע�� : ����� content Ϊ�����ʵ�岻������ ;

����;
map<int, string> _library;

FOR_EACH(elem, _library)
{
	elem.first;
	elem.second.DoSomething();
}
*/
#if !defined FOR_EACH
#define FOR_EACH(elem, ins) for(auto elem : ins)
#endif


/*����������ֻ��forѭ���ļ�д��*/
#if !defined FOR_EACH_VEC
#define FOR_EACH_VEC(origin, ins, it) for(origin::iterator it = ins.begin() ; it != ins.end() ; ++it)
#endif

#if !defined FOR_EACH_MAP
#define FOR_EACH_MAP(origin_front, origin2_back, ins, it) for(origin_front##,##origin2_back::iterator it = ins.begin() ; it != ins.end() ; ++it)
#endif

/*for ѭ�� vector �������Ҫ����ͬһ����Ա�����ĺ궨���д,����Ͳ���Ҫit����,�����ڲ�����д����;
��һ�������� vecԭ�� ��: vector<int>;
�ڶ��������� vector ʵ����;
�������� Ԫ�صĳ�Ա����;
ע�� : ����Ҳֻʵ���� vector ��Ԫ����ʵ������;*/
#if !defined FOR_EACH_VEC_FUN
#define FOR_EACH_VEC_FUN(origin, ins, fun) for(origin::iterator it = ins.begin() ; it != ins.end() ; ++it)\
{\
	it->fun();\
}
#endif

/*for ѭ�� map �� second �������Ҫ����ͬһ����Ա�����ĺ궨���д,����Ͳ���Ҫit����,�����ڲ�����д����;
��һ�������� vecԭ�� ��: map<int, string>;
�ڶ��������� map ʵ����;
�������� second�ĳ�Ա����;
ע�� : ���￴��ȥ������4������,ʵ������ӦΪmap�����е� "," ��,���������������� ## �Ժ��ҵ������취���޸�;
���ֻʵ��Ϊmap���Ǵ��ʵ������,���map����ָ��Ͳ���*/
#if !defined FOR_EACH_MAP_FUN
#define FOR_EACH_MAP_FUN(origin_front, origin2_back, ins, fun) for(origin_front##,##origin2_back::iterator it = ins.begin() ; it != ins.end() ; ++it)\
{\
	it->second.fun();\
}
#endif