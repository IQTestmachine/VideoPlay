#pragma once
#include <string>

typedef unsigned char BYTE;

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

