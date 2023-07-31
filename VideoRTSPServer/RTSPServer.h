#pragma once
#include "Socket.h"
#include <string>
#include "IQtestmachineThread.h"
#include <map>
#include "IQtestmachineQueue.h"
#include "MideaFile.h"
#include "RTPHelper.h"

class RTSPRequest
{
public:
	RTSPRequest();
	RTSPRequest(const RTSPRequest& protocol);
	RTSPRequest& operator=(const RTSPRequest& protocol);
	~RTSPRequest();
	void SetMethod(const IQBuffer& method);
	void SetUrl(const IQBuffer& url);
	void SetSequence(const IQBuffer& seq);
	void SetClientPort(int ports[]);
	void SetSession(const IQBuffer& session);
	int method() const { return m_method; }
	const IQBuffer& url() const { return m_url; }
	const IQBuffer& session() const { return m_session; }
	const IQBuffer& sequence() const { return m_seq; }
	const IQBuffer& port(int index = 0) const { return index ? m_client_port[1] : m_client_port[0]; }
private:
	int m_method;//0 OPTIONS 1 DESCRIBE 2 SETUP 3 PLAY 4 TEARDOWN
	IQBuffer m_url;
	IQBuffer m_session;
	IQBuffer m_seq;
	IQBuffer m_client_port[2];
};

class RTSPReply {
public:
	RTSPReply();
	RTSPReply(const RTSPReply& protocol);
	RTSPReply& operator=(const RTSPReply& protocol);
	~RTSPReply() {}
	IQBuffer toBuffer();
	void SetMethod(int method);
	void SetOptions(const IQBuffer& options);
	void SetSequence(const IQBuffer& seq);
	void SetSdp(const IQBuffer& sdp);
	void SetClientPort(const IQBuffer& port0, const IQBuffer& port1);
	void SetServerPort(const IQBuffer& port0, const IQBuffer& port1);
	void SetSession(const IQBuffer& session);
private:
	int m_method;//0 OPTIONS 1 DESCRIBE 2 SETUP 3 PLAY 4 TEARDOWN
	int m_client_port[2];
	int m_server_port[2];
	IQBuffer m_sdp;
	IQBuffer m_options;
	IQBuffer m_session;
	IQBuffer m_seq;
};

class RTSPSession;
class RTSPServer;
typedef void (*RTSPPLAYCB)(RTSPServer* thiz, RTSPSession& session);

class RTSPSession
{
public:
	RTSPSession();
	RTSPSession(const IQSocket& client);
	RTSPSession(const RTSPSession& session);
	RTSPSession& operator=(const RTSPSession& session);
	int PickRequestAndReply(RTSPPLAYCB cb, RTSPServer* thiz);//接收数据请求, 解析请求, 应答请求
	IQAddress GetClientUDPAddress() const;
	~RTSPSession();
private:
	IQBuffer PickOneLine(IQBuffer& buffer);
	IQBuffer Pick();
	RTSPRequest AnalyseRequest(const IQBuffer& buffer);
	RTSPReply Reply(const RTSPRequest& request);
private:
	IQBuffer m_id;
	IQSocket m_client;
	short m_port;
};

class RTSPServer : public ThreadFuncBase
{
public:
	RTSPServer()
		: m_socket(true), m_status(0), m_pool(4)
	{
		m_threadMain.UpdataWorker(CThreadWorker(this, (FUNCTYPE)&RTSPServer::threadWorker));
		m_h264.Open("./test.h264");
	}
	int Init(const std::string& strIP = "0.0.0.0", short port = 554);
	int Invoke();
	void Stop();
	~RTSPServer();
protected:
	int threadWorker();//返回0继续, 返回负数终止, 返回其他警告
	int ThreadSession();
	static void PlayCallBack(RTSPServer* thiz, RTSPSession& session);
	void UdpWorker(const IQAddress& client);
private:
	static SocketIniter m_initer;
	IQSocket m_socket;
	IQAddress m_addr;
	int m_status;//0 未初始化 1 初始化完成 2 正在运行 3 关闭
	CIQtestmachineThread m_threadMain;
	IQtestmachinePool m_pool;
	CIQtestmachineQueue<RTSPSession> m_lstSession;
	RTPHelper m_helper;
	MideaFile m_h264;
};

