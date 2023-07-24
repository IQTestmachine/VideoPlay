#include "pch.h"
#include "IQVlc.h"

IQVlc::IQVlc()
{
    m_instance = libvlc_new(0, NULL);
    m_media = NULL;
    m_player = NULL;
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
    if (m_instance == NULL) {
        return -1;
    }
    m_media = libvlc_media_new_location(m_instance, strUrl.c_str());
    if (m_media == NULL) {
        return -2;
    }
    m_player = libvlc_media_player_new_from_media(m_media);
    if (m_media == NULL) {
        return -3;
    }
    return 0;
}

int IQVlc::SetHwnd(HWND hWnd)
{
    if (m_instance == NULL || m_media == NULL) {
        return -1;
    }
    libvlc_media_player_set_hwnd(m_player, hWnd);
    return 0;
}

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
    return libvlc_media_player_get_position(m_player);
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
