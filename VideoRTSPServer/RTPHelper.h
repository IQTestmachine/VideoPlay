#pragma once
#include "base.h"
#include "Socket.h"

class RTPHeader
{
public://见RTP header定义图
	unsigned short csrccount : 4;
	unsigned short extension : 1;
	unsigned short padding : 1;
	unsigned short version : 2;//位域
	unsigned short pytype : 7;
	unsigned short mark : 1;
	unsigned short serial;
	unsigned timestamp;
	unsigned ssrc;
	unsigned csrc[15];
public:
	RTPHeader();
	RTPHeader(const RTPHeader& header);
	RTPHeader& operator=(const RTPHeader& header);
	operator IQBuffer();
};

class RTPFrame//RTP数据包类, 用于服务端向客户端发送h264解析来的数据
{
public:
	RTPHeader m_head;
	IQBuffer m_pyload;
	operator IQBuffer();//隐式转换, 当发送数据时, 可以自动让对象成为RTP数据包的格式(头部+载荷)
};

class RTPHelper//用于把h264解析来的数据帧分片并发送
{
public:
	RTPHelper() :timestamp(0), m_udp(false) {
		//m_udp.Bind(IQAddress("0.0.0.0", (short)55000));
	}
	~RTPHelper() {}
	int SendMediaFrame(RTPFrame& rtpframe, IQBuffer& frame, const IQAddress& client);//把h264解析来的数据帧分片并发送
private:
	int GetFrameSepSize(IQBuffer& frame);
	int SendFrame(const IQBuffer& frame, const IQAddress& client);
	DWORD timestamp;
	IQSocket m_udp;
};

