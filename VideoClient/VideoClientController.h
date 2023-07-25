#pragma once
#include "IQVlc.h"
#include "VideoClientDlg.h"

enum IQVlcCommand {
	IQVLC_PLAY,
	IQVLC_PAUSE,
	IQVLC_STOP,
	IQVLC_GET_VOLUME,
	IQVLC_GET_POSITION,
	IQVLC_GET_LENGTH
};

class VideoClientController
{
public:
	VideoClientController();
	~VideoClientController();
	int Init(CWnd*& pWnd);
	int Invoke();
	int SetMedia(const std::string& strUrl);
	float VideoCtrl(IQVlcCommand cmd);
	void SetPosition(float pos);
	int SetWnd(HWND hwnd);
	void SetVolume(int volume);
	VlcSize GetMediaInfo();
	std::string Unicode2Utf8(const std::wstring& strIn);
protected:
	IQVlc m_vlc;
	CVideoClientDlg m_dlg;
};

