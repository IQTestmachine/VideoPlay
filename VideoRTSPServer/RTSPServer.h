#pragma once
#include "Socket.h"
#include <string>
#include "IQtestmachineThread.h"
#include <map>

class RTSPRequest
{
public:
	RTSPRequest();
	RTSPRequest(const RTSPRequest& protoclo);
	RTSPRequest& operator=(const RTSPRequest& protocol);
	~RTSPRequest();
private:
	int m_method;//0 OPTIONS 1 DESCRIBE 2 SETUP 3 PLAY 4 TEARDOWN
};

class RTSPReply
{

};
class RTSPSession
{
public:
	RTSPSession();
	RTSPSession(const RTSPSession& session);
	RTSPSession& operator&(const RTSPSession& session);
	~RTSPSession();
};

class RTSPServer : public ThreadFuncBase
{
public:
	RTSPServer()
		: m_socket(true), m_status(0)
	{}
	int Init(const std::string& strIP = "0.0.0.0", short port = 554);
	int Invoke();
	void Stop();
	~RTSPServer();
protected:
	int ThreadWorker();
	RTSPRequest AnalyseRequest(const std::string& data);
	RTSPReply MakeReplay(const RTSPRequest& request);
	int ThreadSession();
private:
	IQSocket m_socket;
	int m_status;//0 未初始化 1 初始化完成 2 正在运行 3 关闭
	CIQtestmachineThread m_threadMain;
	IQtestmachinePool m_pool;
	std::map<std::string, RTSPSession> m_mapSession;
	static SocketIniter m_initer;
};

