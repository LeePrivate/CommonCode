/*!
 * \file Log.h
 *
 * \author lixiang
 * \date ���� 2014
 *
 * �������:���̰߳�ȫ,������̶߳�ͬһ����־�ļ����в���,��Ҫ�Լ����̰߳�ȫ�Ĵ���;
 *
 *ʹ�÷���:����ͷ�ļ��Ժ�,ֱ����Ҫ�����־�ĵط�ʹ�ö���ĺ�,����
 *�����Ĭ�ϵ���־�ļ� DefaultLog("%s output &d", char, int);
 *�����ָ���ļ�������־(�����¼��Ϣ���Ե�����һ���ļ������֮���) SpecityLog("�ļ���","%s output &d", char, int );
 *
 *ע��: ÿ����־�ļ�,��Log�ഴ����ʱ����Ѿ�����Ĭ��app��ʽ����;
 */

#pragma once

#include "LeeConfig.h"

class LogOpt											//��־����(���������ȫû�õ�);
{
	bool		_bAddTimestamp;						//�Ƿ�ʹ��ʱ���;
	bool		_bDebugPrint;							//�Ƿ���Debugģʽ print;
	uint32	_CacheSize;								//�����С;
	uint32	_CacheTime;								//����ʱ����;
};

class Log
{
public:
	Log(const string& FileName, std::ios::openmode OpenMode = ios::app, bool AddTimestamp = true, bool DebugPrint = true);		//ios::out ������ļ���ɾ���ؽ�, ios::app ���ļ��ʹӺ������;

	virtual ~Log();

	const string& GetFileName() const;

	virtual void Write(const char* msg);								//д��־;

	virtual void Update();													//����(������ʲô��ľ��....);

protected:
	std::ofstream _File;
	string	_FileName;					//��־�ļ���;
	bool		_bAddTimestamp;			//�Ƿ�ʹ��ʱ���;
	bool		_bDebugPrint;				//�Ƿ���Debugģʽ print;

//todo:���ӻ���ģʽ,�ﵽһ��������־������һ��ʱ����,������д��Ӳ��,����Ӳ��IO����(�Ժ���д);
};

class LogMgr												//��־����
{
public:
	LogMgr();

	~LogMgr();

	//void AddLog(Log* log);								//�����־(ȥ�����������־�ķ�ʽʹ�����������Ի��ķ�ʽ,ͳһ��ʽ);

	string AddLog(string fileName, std::ios::openmode openMode = ios::app, bool addTimestamp = true, bool debugPrint = true);		//�����־ ios::out ������ļ���ɾ���ؽ�, ios::app ���ļ��ʹӺ������ ��������������ӽ�LogMap���ļ���, ӦΪ���иı��ļ��������;

	void WriteDefaultLog(const char* format, ...);			//��¼��־��Ĭ��Log;

	void WriteSpecifyLog(string fileName, const char* format, ...);			//��¼��־(ָ���ļ�,��Ҫ��֮ǰAddһ��Log �� Log Map ��);

	bool SetDefaultLog(const string& fileName);			//����Ĭ����־;

	void Updata();		//����;

	void VerifyFileName(string& fileName);						//�ڼ�������־�ļ�ʱ��֤��־�ļ���,���û�м�.txt,���Զ�����,�Է�����д�ļ�����׺�����;

	SINGLE_MODE(LogMgr);							

protected:
	typedef map<string, Log*>		LogMap;
	
	LogMap	_mapLog;
	Log*			_DefaultLog;

	static const int s_MaxLogLen = 16 *1024;				//������־��󳤶�;
};

//�����Ĭ����־;
#define DefaultLog(...) LogMgr::GetSingle().WriteDefaultLog(__VA_ARGS__)

//�����ָ����־,��Ҫ�����ļ���,���������֮ǰҪ�Ѿ�Add�� Log map ��;
#define SpecifyLog(_LOG_NAME_, ...) LogMgr::GetSingle().WriteSpecifyLog(_LOG_NAME_, __VA_ARGS__)


