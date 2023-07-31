#pragma once
#include "base.h"

class MideaFile
{
public:
	MideaFile();
	~MideaFile();
	int Open(const IQBuffer& path, int nType = 96);
	//如果buffer的size为0, 则表示没有帧了
	IQBuffer ReadOneFrame();
	void Close();
	//重置文件读取指针到文件头部
	void Reset();
private:
	//返回-1表明查找失败
	long FindH264Head(int& headsize);
	IQBuffer ReadH264Frame();
private:
	long m_size;
	FILE* m_file;
	IQBuffer m_filepath;
	//96 H264
	int m_type;
};

