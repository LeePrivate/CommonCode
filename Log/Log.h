/********************************************************************
	created:	2014/10/23
	created:	23:10:2014   17:13

	author:		����;
	
	purpose:	��־���:���̰߳�ȫ,������̶߳�ͬһ����־�ļ����в���,��Ҫ�Լ����̰߳�ȫ�Ĵ���;
	
	ʹ�÷���:����ͷ�ļ��Ժ�,ֱ����Ҫ�����־�ĵط�ʹ�ö���ĺ�,����;
	�����Ĭ�ϵ���־�ļ� DefaultLog("%s output &d", char, int);
	ע��Ĭ����־����Log����ʱ��Ϊ�ļ���;
	�����ָ���ļ�������־(�����¼��Ϣ���Ե�����һ���ļ������֮���) SpecityLog("�ļ���","%s output &d", char, int );
	
	ע��: ÿ����־�ļ�,��Log�ഴ����ʱ����Ѿ�����Ĭ��app��ʽ����,��־��������ʱ��ÿ����Сʱ���ⴴ��һ���ļ��������־;
	
	ʵ�ʹ����������������������޸�;
	�Ժ�������д�����ݿ����־ϵͳ,�����ļ���С��һ���ļ����������־����;
*********************************************************************/



#pragma once

#include "Config.h"
#include "DataTimeUtil.h"
#include "StringUtil.h"


//��־������Ϣ;
struct LogOpt											
{
	//��־�ļ���;
	string	_sLogName;			

	//��־����ʱ��;
	string	_sCreateTime;	

	//��ģʽ ios::out ������ļ���ɾ���ؽ�, ios::app ���ļ��ʹӺ������;
	std::ios::openmode _OpenMode;	

	//�Ƿ�ʹ��ʱ���;
	bool		_bAddTimestamp;		

	//�Ƿ���Debugģʽ print;
	bool		_bDebugPrint;		

	//�����С(��ʱû���õ�);
	uint32	_CacheSize;		

	//����ʱ����(��ʱû���õ�);
	uint32	_CacheTime;								

	LogOpt()
		:_sLogName("DefaultLog.txt")
		,_sCreateTime(DataTimeUtil::GetYMD_HMS_String())
		,_OpenMode(ios::app)
		,_bAddTimestamp(true)
		,_bDebugPrint(true)
		,_CacheSize(0)
		,_CacheTime(0)
	{
	}
};

class Log
{
public:
	Log(LogOpt logOpt);			

	virtual ~Log();

	const string& GetLogName() const;

	//д��־;
	virtual void Write(const char* msg);								

	//����(������ʲô��ľ��....);
	virtual void Update();													

	//��־��ϸ������Ϣ;
	LogOpt				_LogOpt;

protected:
	std::ofstream	_stdOF;												
	

//todo:���ӻ���ģʽ,�ﵽһ��������־������һ��ʱ����,������д��Ӳ��,����Ӳ��IO����(�Ժ���д);
};



//��־����;
class LogMgr				
{
public:
	LogMgr();

	~LogMgr();

	string AddLog(LogOpt logOpt);		//�����־ ios::out ������ļ���ɾ���ؽ�, ios::app ���ļ��ʹӺ������ ��������������ӽ�LogMap���ļ���, ӦΪ���иı��ļ��������;

	void WriteDefaultLog(const char* format, ...);									//��¼��־��Ĭ��Log;

	void WriteSpecifyLog(string fileName, const char* format, ...);			//��¼��־(ָ���ļ�,��Ҫ��֮ǰAddһ��Log �� Log Map ��);

	bool SetDefaultLog(const string& fileName);									//����Ĭ����־;

	void Updata();																					//����;

	void VerifyFileName(string& fileName);												//�ڼ�������־�ļ�ʱ��֤��־�ļ���,���û�м�.txt,���Զ�����,�Է�����д�ļ�����׺�����;

	string GetDefaultLogName();															//�õ�Ĭ����־���ļ���;

	void SetLogReCreateInterval(int secTime);											//��������������־��ʱ����(Ĭ������Сʱ,ÿ�������г��򶼻������µ���־);

	SINGLE_MODE(LogMgr);							

protected:
	typedef map<string, Log*>		LogMap;
	
	LogMap	_mapLog;

	Log*			_DefaultLog;

	//��־�������ɼ��ʱ��(Ĭ����:7200 ��Сʱ);
	int			_LogReCreateInterval;		

	//������־��󳤶�;
	static const int s_MaxLogLen = 16 *1024;				
};

//�õ���־������;
#define GetLogMgr LogMgr::GetSingle()		

//�����Ĭ����־;
#define DefaultLog(...) LogMgr::GetSingle()->WriteDefaultLog(__VA_ARGS__)

//�����ָ����־,��Ҫ�����ļ���,���������֮ǰҪ�Ѿ�Add�� Log map ��;
#define SpecifyLog(_LOG_NAME_, ...) LogMgr::GetSingle()->WriteSpecifyLog(_LOG_NAME_, __VA_ARGS__)


