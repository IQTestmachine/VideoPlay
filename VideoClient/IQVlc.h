#pragma once
#include "vlc.h"
#include <string>

class VlcSize
{
public:
	int nWidth;
	int nHeight;
	VlcSize(int width = 0, int height = 0) {
		nWidth = width;
		nHeight = height;
	}
	VlcSize(const VlcSize& size) {
		nWidth = size.nWidth;
		nHeight = size.nHeight;
	}
	VlcSize& operator=(const VlcSize& size) {
		if (this != &size) {
			nWidth = size.nWidth;
			nHeight = size.nHeight;
		}
		return* this;
	}
	~VlcSize() { }
};

class IQVlc
{
public:
	IQVlc();
	~IQVlc();
	//如果传入的url含义中文, 请使用UTF-8编码格式
	int SetMedia(const std::string& strUrl);
	int SetHwnd(HWND hWnd);
	int Play();
	int Pause();
	int Stop();
	float GetPostion();
	void SetPostion(float pos);
	int GetVolume();
	void SetVolume(int volume);
	VlcSize GetMediaInfo();
protected:
	libvlc_instance_t* m_instance;
	libvlc_media_t* m_media;
	libvlc_media_player_t* m_player;
};

