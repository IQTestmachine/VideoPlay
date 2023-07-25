#include "pch.h"
#include "VideoClientController.h"

VideoClientController::VideoClientController()
{
	m_dlg.m_controller = this;
}

VideoClientController::~VideoClientController()
{
}

int VideoClientController::Init(CWnd*& pWnd)
{
	pWnd = &m_dlg;
	return 0;
}

int VideoClientController::Invoke()
{
	INT_PTR nResponse = m_dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
	return nResponse;
}

int VideoClientController::SetMedia(const std::string& strUrl)
{
	return m_vlc.SetMedia(strUrl);
}

float VideoClientController::VideoCtrl(IQVlcCommand cmd)
{
	switch (cmd)
	{
	case IQVLC_PLAY:
		return float(m_vlc.Play());
	case IQVLC_PAUSE:
		return float(m_vlc.Pause());
	case IQVLC_STOP:
		return float(m_vlc.Stop());
	case IQVLC_GET_VOLUME:
		return float(m_vlc.GetVolume());
	case IQVLC_GET_POSITION:
		return float(m_vlc.GetPostion());
	case IQVLC_GET_LENGTH:
		return float(m_vlc.GetLength());
	default:
		break;
	}
	return -1.0f;
}

void VideoClientController::SetPosition(float pos)
{
	m_vlc.SetPostion(pos);
}

int VideoClientController::SetWnd(HWND hwnd)
{
	return m_vlc.SetHwnd(hwnd);
}

void VideoClientController::SetVolume(int volume)
{
	m_vlc.SetVolume(volume);
}

VlcSize VideoClientController::GetMediaInfo()
{
	return m_vlc.GetMediaInfo();
}

std::string VideoClientController::Unicode2Utf8(const std::wstring& strIn)
{
	return m_vlc.Unicode2Utf8(strIn);
}


