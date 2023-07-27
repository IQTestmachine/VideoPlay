#pragma once
#include <WinSock2.h>
#include <share.h>

class Socket
{
public:
	//nType 0 TCP 1 UDP
	Socket(bool bIsTcp = true) {
		m_sock = INVALID_SOCKET;
		if (bIsTcp) {
			m_sock = socket(PF_INET, SOCK_STREAM, 0);
		}
		else {
			m_sock = socket(PF_INET, SOCK_DGRAM, 0);
		}
	}
	Socket(SOCKET s) {
		m_sock = s;
	}
	operator SOCKET() {
		return m_sock;
	}
	void Close() {
		if (m_sock != INVALID_SOCKET) {
			SOCKET temp = m_sock;
			m_sock = INVALID_SOCKET;
			closesocket(temp);
		}
	}
	~Socket() {
		Close();
	}

private:
	SOCKET m_sock;
};

class IQSocket
{
public:
	IQSocket(bool isTcp = true) 
		: m_socket(new Socket(isTcp))
	{}
	IQSocket(const IQSocket& sock)
		: m_socket(sock.m_socket) 
	{}
	IQSocket& operator=(const IQSocket& sock) {
		if (this != &sock) {
			m_socket = sock.m_socket;
		}
		return *this;
	}
	~IQSocket() {
		m_socket.reset();
	}
	operator SOCKET() {
		return *m_socket;
	}
private:
	std::shared_ptr<Socket> m_socket;

};

class SocketIniter
{
public:
	SocketIniter() {
		WSADATA wsa;
		WSAStartup(MAKEWORD(2, 2), &wsa);
	}
	~SocketIniter() {
		WSACleanup();
	}
};
