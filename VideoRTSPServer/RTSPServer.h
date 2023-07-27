#pragma once
#include "Socket.h"
#include <string>
#include "IQtestmachineThread.h"
#include <map>
#include "IQtestmachineQueue.h"

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
public:
	RTSPReply();
	RTSPReply(const RTSPRequest& protoclo);
	RTSPReply& operator=(const RTSPRequest& protocol);
	~RTSPReply();
	IQBuffer toBuffer();
private:
	int m_method;//0 OPTIONS 1 DESCRIBE 2 SETUP 3 PLAY 4 TEARDOWN
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
		: m_socket(true), m_status(0), m_pool(4)
	{
		m_threadMain.UpdataWorker(CThreadWorker(this, (FUNCTYPE)&RTSPServer::threadWorker));
	}
	int Init(const std::string& strIP = "0.0.0.0", short port = 554);
	int Invoke();
	void Stop();
	~RTSPServer();
protected:
	int threadWorker();//����0����, ���ظ�����ֹ, ������������
	RTSPRequest AnalyseRequest(const std::string& data);
	RTSPReply MakeReplay(const RTSPRequest& request);
	int ThreadSession();
private:
	IQSocket m_socket;
	IQAddress m_addr;
	int m_status;//0 δ��ʼ�� 1 ��ʼ����� 2 �������� 3 �ر�
	CIQtestmachineThread m_threadMain;
	IQtestmachinePool m_pool;
	std::map<std::string, RTSPSession> m_mapSession;
	static SocketIniter m_initer;
	CIQtestmachineQueue<IQSocket> m_clients;
};

