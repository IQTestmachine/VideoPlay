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
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
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


