﻿// VideoRTSPServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "RTSPServer.h"
#include <iostream>

int main()
{
    RTSPServer server;
    server.Init();
    server.Invoke();
    std::cout << "press any to stop...." << std::endl;
    getchar();
    server.Stop();
}
