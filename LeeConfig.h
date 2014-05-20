#pragma once

#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <queue>



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

