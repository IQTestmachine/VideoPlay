#pragma once
#include "base.h"

class MideaFile
{
public:
	MideaFile();
	~MideaFile();
	int Open(const IQBuffer& path, int nType = 96);
	//���buffer��sizeΪ0, ���ʾû��֡��
	IQBuffer ReadOneFrame();
	void Close();
	//�����ļ���ȡָ�뵽�ļ�ͷ��
	void Reset();
private:
	//����-1��������ʧ��
	long FindH264Head(int& headsize);
	IQBuffer ReadH264Frame();
private:
	long m_size;
	FILE* m_file;
	IQBuffer m_filepath;
	//96 H264
	int m_type;
};

