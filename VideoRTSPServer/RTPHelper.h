#pragma once
#include "base.h"
#include "Socket.h"

class RTPHeader
{
public://��RTP header����ͼ
	unsigned short csrccount : 4;
	unsigned short extension : 1;
	unsigned short padding : 1;
	unsigned short version : 2;//λ��
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

class RTPFrame//RTP���ݰ���, ���ڷ������ͻ��˷���h264������������
{
public:
	RTPHeader m_head;
	IQBuffer m_pyload;
	operator IQBuffer();//��ʽת��, ����������ʱ, �����Զ��ö����ΪRTP���ݰ��ĸ�ʽ(ͷ��+�غ�)
};

class RTPHelper//���ڰ�h264������������֡��Ƭ������
{
public:
	RTPHelper() :timestamp(0), m_udp(false) {
		//m_udp.Bind(IQAddress("0.0.0.0", (short)55000));
	}
	~RTPHelper() {}
	int SendMediaFrame(RTPFrame& rtpframe, IQBuffer& frame, const IQAddress& client);//��h264������������֡��Ƭ������
private:
	int GetFrameSepSize(IQBuffer& frame);
	int SendFrame(const IQBuffer& frame, const IQAddress& client);
	DWORD timestamp;
	IQSocket m_udp;
};

