/*
 * @Author: Qizhou 
 * @Date: 2020-10-20 14:16:47 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-20 14:17:10
 */
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/Buffer.h>
#include <iostream>

#include "common/myLog.h"

using namespace muduo;
using namespace muduo::net;

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Usage: server <address> <port> <threads>\n");
    }
    else
    {
        LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
        Logger::setLogLevel(Logger::WARN);

        const char *ip = argv[1];
        uint16_t port = static_cast<uint16_t>(atoi(argv[2]));
        InetAddress listenAddr(ip, port);
        int threadCount = atoi(argv[3]);

        EventLoop loop;

        TcpServer server(&loop, listenAddr, "TcpKeeper");

        server.setConnectionCallback(onConnection);
        server.setMessageCallback(onMessage);

        if (threadCount > 1)
        {
            server.setThreadNum(threadCount);
        }

        server.start();
        loop.loop();
    }
}