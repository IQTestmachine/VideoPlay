#include "pch.h"
#include "IQVlc.h"

IQVlc::IQVlc()
{
    m_instance = libvlc_new(0, NULL);
    m_media = NULL;
    m_player = NULL;
    m_hwnd = NULL;
}

IQVlc::~IQVlc()
{
    if (m_player != NULL) {
        libvlc_media_player_t* temp = m_player;
        m_player = NULL;
        libvlc_media_player_release(temp);
    }
    if (m_media != NULL) {
        libvlc_media_t* temp2 = m_media;
        m_media = NULL;
        libvlc_media_release(temp2);
    }
    if (m_instance != NULL) {
        libvlc_instance_t* temp3 = m_instance;
        m_instance = NULL;
        libvlc_release(temp3);
    }
}

int IQVlc::SetMedia(const std::string& strUrl)
{
    if (m_instance == NULL || m_hwnd == NULL) {
        return -1;
    }
    if (strUrl == m_url) {
        return 0;
    }
    m_url = strUrl;
    if (m_media != NULL) {
        libvlc_media_release(m_media);
        m_media = NULL;
    }
    m_media = libvlc_media_new_location(m_instance, strUrl.c_str());
    if (m_media == NULL) {
        return -2;
    }
    if (m_player != NULL) {
        libvlc_media_player_release(m_player);
        m_player = NULL;
    }
    m_player = libvlc_media_player_new_from_media(m_media);
    if (m_media == NULL) {
        return -3;
    }
    
    CRect rect;
    GetWindowRect(m_hwnd, rect);
    std::string strRatio = "";
    strRatio.resize(32);
#pragma warning(suppress : 4996)
    sprintf((char*)strRatio.c_str(), "%d:%d", rect.Width(), rect.Height());
    libvlc_video_set_aspect_ratio(m_player, strRatio.c_str());
    libvlc_media_player_set_hwnd(m_player, m_hwnd);
    return 0;
}

#ifdef WIN32
int IQVlc::SetHwnd(HWND hWnd)
{
    m_hwnd = hWnd;
    return 0;
}
#endif

int IQVlc::Play()
{
    if (m_instance == NULL || m_media == NULL || m_player == NULL) {
        return -1;
    }
    libvlc_media_player_play(m_player);
    return 0;
}

int IQVlc::Pause()
{
    if (m_instance == NULL || m_media == NULL || m_player == NULL) {
        return -1;
    }
    libvlc_media_player_pause(m_player);
    return 0;
}

int IQVlc::Stop()
{
    if (m_instance == NULL || m_media == NULL || m_player == NULL) {
        return -1;
    }
    libvlc_media_player_stop(m_player);
    return 0;
}

float IQVlc::GetPostion()
{
    if (m_instance == NULL || m_media == NULL || m_player == NULL) {
        return -1;
    }
    float nowpos = libvlc_media_player_get_position(m_player);
    return nowpos;
}

void IQVlc::SetPostion(float pos)
{
    if (m_instance == NULL || m_media == NULL || m_player == NULL) {
        return;
    }
    libvlc_media_player_set_position(m_player, pos);
}

int IQVlc::GetVolume()
{
    if (m_instance == NULL || m_media == NULL || m_player == NULL) {
        return -1;
    }
    return libvlc_audio_get_volume(m_player);
}

float IQVlc::GetLength()
{
    if (m_instance == NULL || m_media == NULL || m_player == NULL) {
        return -0.1f;
    }
    libvlc_time_t tm = libvlc_media_player_get_length(m_player);
    float ret = tm / 1000.0f;
    return ret;
}

void IQVlc::SetVolume(int volume)
{
    if (m_instance == NULL || m_media == NULL || m_player == NULL) {
        return;
    }
    libvlc_audio_set_volume(m_player, volume);
}

VlcSize IQVlc::GetMediaInfo()
{
    if (m_instance == NULL || m_media == NULL || m_player == NULL) {
        return VlcSize(-1, -1);
    }
    return VlcSize(libvlc_video_get_width(m_player), libvlc_video_get_height(m_player));
}

std::string IQVlc::Unicode2Utf8(const std::wstring& strIn)
{
    std::string str;
    int length = ::WideCharToMultiByte(CP_UTF8, 0, strIn.c_str(), strIn.size(), NULL, 0, NULL, NULL);
    str.resize(length + 1);
    ::WideCharToMultiByte(CP_UTF8, 0, strIn.c_str(), strIn.size(), (LPSTR)str.c_str(), length, NULL, NULL);
    return str;
}
