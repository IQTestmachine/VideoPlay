#pragma once
#include <WinSock2.h>
#include <string>
#include <memory>
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#pragma comment(lib, "ws2_32.lib")

class IQBuffer : public std::string
{
public:
	IQBuffer(const char* str) {
		resize(strlen(str));
		memcpy((void*)c_str(), str, size());
	}
	IQBuffer(size_t size = 0) : std::string() {
		if (size > 0) {
			resize(size);
			memset(*this, 0, this->size());
		}
	}
	IQBuffer(void* buffer, size_t size) : std::string() {
		resize(size);
		memcpy((void*)c_str(), buffer, size);
	}

	~IQBuffer() {
		std::string::~basic_string();
	}

	operator char* () const { return (char*)c_str(); }
	operator const char* () const { return (const char*)c_str(); }
	operator BYTE* () const { return (BYTE*)c_str(); }
	operator void* () const { return (void*)c_str(); }
	void Update(void* buffer, size_t size) {
		resize(size);
		memcpy((void*)c_str(), buffer, size);
	}
	void Zero() {
		if (size() > 0) {
			memset((void*)c_str(), 0, size());
		}
	}
	IQBuffer& operator<<(const IQBuffer& str) {
		if (this != str) {
			*this += str;
		}
		else {
			IQBuffer tmp = str;
			*this += tmp;
		}
		return *this;
	}
	IQBuffer& operator<<(const std::string& str) {
		*this += str;
		return *this;
	}
	IQBuffer& operator<<(const char* str) {
		*this += IQBuffer(str);
		return *this;
	}
	IQBuffer& operator<<(int data) {
		char s[16] = "";
		snprintf(s, sizeof(s), "%d", data);
		*this += s;
		return *this;
	}
	const IQBuffer& operator>>(int& data) const {
		data = atoi(c_str());
		return *this;
	}
	const IQBuffer& operator>>(short& data) const {
		data = (short)atoi(c_str());
		return *this;
	}
};

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
	void Close() {
		if (m_sock != INVALID_SOCKET) {
			SOCKET temp = m_sock;
			m_sock = INVALID_SOCKET;
			closesocket(temp);
		}
	}
	operator SOCKET() {
		return m_sock;
	}
	~Socket() {
		Close();
	}
private:
	SOCKET m_sock;
};

class IQAddress
{
public:
	IQAddress() {
		m_port = -1;
		memset(&m_addr, 0, sizeof(m_addr));
		m_addr.sin_family = AF_INET;
	}
	IQAddress(const std::string& ip, short port) {
		m_ip = ip;
		m_port = port;
		m_addr.sin_port = htons(port);
		m_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	}
	IQAddress(const IQAddress& addr) {
		m_ip = addr.m_ip;
		m_port = addr.m_port;
		memcpy(&m_addr, &addr.m_addr, sizeof(sockaddr_in));
	}
	IQAddress& operator=(const IQAddress& addr)
	{
		if (this != &addr) {
			m_ip = addr.m_ip;
			m_port = addr.m_port;
			memcpy(&m_addr, &addr.m_addr, sizeof(sockaddr_in));
		}
		return *this;
	}
	IQAddress& operator=(short port) {
		m_port = (unsigned short)port;
		m_addr.sin_port = htons(port);
		return *this;
	}
	~IQAddress() {}
	void Update(const std::string& ip, short port) {
		m_ip = ip;
		m_port = port;
		m_addr.sin_port = htons(port);
		m_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	}
	operator const sockaddr* () const { return (sockaddr*)&m_addr; }
	operator sockaddr* () { return (sockaddr*)&m_addr; }
	operator sockaddr_in* () { return &m_addr; }
	int size()const { return sizeof(sockaddr_in); }
private:
	std::string m_ip;
	unsigned short m_port;
	sockaddr_in m_addr;
};

class IQSocket
{
public:
	IQSocket(bool isTcp = true)
		:m_socket(new Socket(isTcp)),
		m_istcp(isTcp)
	{}
	IQSocket(const IQSocket& sock)
		:m_socket(sock.m_socket),
		m_istcp(sock.m_istcp)
	{}
	IQSocket(SOCKET sock, bool isTcp) :
		m_socket(new Socket(sock)),
		m_istcp(isTcp)
	{}

	IQSocket& operator=(const IQSocket& sock) {
		if (this != &sock)m_socket = sock.m_socket;
		return *this;
	}
	~IQSocket() {
		m_socket.reset();
	}

	operator SOCKET() const {
		return *m_socket;
	}

	int Bind(const IQAddress& addr) {
		if (m_socket == nullptr) {
			m_socket.reset(new Socket(m_istcp));
		}
		return bind(*m_socket, addr, addr.size());
	}

	int Listen(int backlog = 5) {
		return listen(*m_socket, backlog);
	}

	IQSocket Accept(IQAddress& addr) {
		int len = addr.size();
		if (m_socket == nullptr)return IQSocket(INVALID_SOCKET, true);
		SOCKET server = *m_socket;
		if (server == INVALID_SOCKET)return IQSocket(INVALID_SOCKET, true);
		SOCKET s = accept(server, addr, &len);
		return IQSocket(s, m_istcp);
	}

	int Connect(const IQAddress& addr) {
		return connect(*m_socket, addr, addr.size());
	}

	int Recv(IQBuffer& buffer) {
		return recv(*m_socket, buffer, buffer.size(), 0);
	}

	int Send(const IQBuffer& buffer) {
		printf("send(%d):[%s]\r\n", buffer.size(), (char*)buffer);
		int index = 0;
		char* pData = buffer;
		while (index < (int)buffer.size()) {
			int ret = send(*m_socket, pData + index, buffer.size() - index, 0);
			if (ret < 0)return ret;
			if (ret == 0)break;
			index += ret;
		}
		return index;
	}

	void Close() {
		m_socket.reset();
	}

private:
	std::shared_ptr<Socket> m_socket;
	bool m_istcp;
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
