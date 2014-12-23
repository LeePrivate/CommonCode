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
#include <stdarg.h>							//va_list va_start ..使用;
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

//鍗曚緥妯″紡,鏇村噯纭?
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

/*----------------------------------------------------------------------------------------各种 FOR_EACH 简写宏定义----------------------------------------------------------*/

/*
注 : 这个宏只能在vs2010以上的版本才能编译通过, vs2010 不支持C++11;
使用C++11的写法,ins 为 stl 任意的容器 vector map 等的定义实体, elem 为容器内元素变量名(任意自定);
这种写法更加简洁;
如:content 为 vector<string> 那么 elem 为每一个string的引用;
如:content 为 map<int, string> 那么 elem 为每一个pair的应用, elem.second 这样来用;
注意 : 这里的 content 为定义的实体不是类型 ;

列子;
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


/*下面这两个只是for循环的简写宏*/
#if !defined FOR_EACH_VEC
#define FOR_EACH_VEC(origin, ins, it) for(origin::iterator it = ins.begin() ; it != ins.end() ; ++it)
#endif

#if !defined FOR_EACH_MAP
#define FOR_EACH_MAP(origin_front, origin2_back, ins, it) for(origin_front##,##origin2_back::iterator it = ins.begin() ; it != ins.end() ; ++it)
#endif

/*for 循环 vector 特殊的需要调用同一个成员函数的宏定义简写,这个就不需要it名了,反正内部帮你写好了;
第一个参数是 vec原型 如: vector<int>;
第二个参数是 vector 实体名;
第三个是 元素的成员函数;
注意 : 这种也只实用于 vector 中元素是实体的情况;*/
#if !defined FOR_EACH_VEC_FUN
#define FOR_EACH_VEC_FUN(origin, ins, fun) for(origin::iterator it = ins.begin() ; it != ins.end() ; ++it)\
{\
	it->fun();\
}
#endif

/*for 循环 map 的 second 特殊的需要调用同一个成员函数的宏定义简写,这个就不需要it名了,反正内部帮你写好了;
第一个参数是 vec原型 如: map<int, string>;
第二个参数是 map 实体名;
第三个是 second的成员函数;
注意 : 这里看上去宏是有4个参数,实际上是应为map定义中的 "," 号,这里迫于无奈用了 ## 以后找到其他办法来修改;
这个只实用为map中是存放实体的情况,如果map中是指针就不行*/
#if !defined FOR_EACH_MAP_FUN
#define FOR_EACH_MAP_FUN(origin_front, origin2_back, ins, fun) for(origin_front##,##origin2_back::iterator it = ins.begin() ; it != ins.end() ; ++it)\
{\
	it->second.fun();\
}
#endif