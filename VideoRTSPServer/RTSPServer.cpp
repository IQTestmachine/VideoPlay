#include "RTSPServer.h"

int RTSPServer::Init(const std::string& strIP, short port)
{
    m_addr.Update(strIP, port);
    m_socket.Bind(m_addr);
    m_socket.Listen();
    return 0;
}

int RTSPServer::Invoke()
{
    m_threadMain.Start();
    return 0;
}

void RTSPServer::Stop()
{
    m_socket.Close();
    m_threadMain.Stop();
    m_pool.Stop();
}

RTSPServer::~RTSPServer()
{
    Stop();
}

int RTSPServer::threadWorker()
{
    IQAddress client_addr;
    IQSocket client = m_socket.Accept(client_addr);
    if (client != INVALID_SOCKET) {
        m_clients.PushBack(client);
        m_pool.DispatchWorker(CThreadWorker(this, (FUNCTYPE)&RTSPServer::ThreadSession));
    }
    return 0;
}

int RTSPServer::ThreadSession()
{
    //TODO:接收数据请求, 解析请求, 应答请求
    //TODO:传参
    IQSocket client;//TODO:能否拿到
    IQBuffer buffer(1024 * 16);
    int len = client.Recv(buffer);
    if (len <= 0) {
        //TODO:清理掉client
        return -1;
    }
    buffer.resize(len);
    RTSPRequest req = AnalyseRequest(buffer);
    RTSPReply ack = MakeReplay(req);
    client.Send(ack.toBuffer());
    return 0;
}
