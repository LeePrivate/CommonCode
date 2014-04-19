#pragma once

#include <iostream>
#include <string>
//#include <boost/filesystem.hpp>
//#include <boost/locale/encoding.hpp>

using namespace std;

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long long uint64;
typedef long long int64;

//单例模式,更准确;
#define SINGLE_MODE( ClassName ) \
	static ClassName& GetSingle() \
{ \
	static ClassName s_##ClassName; \
	return s_##ClassName; \
}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(varType var){ varName = var; }