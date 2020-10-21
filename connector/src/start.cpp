/*
 * @Author: Qizhou 
 * @Date: 2020-10-20 18:54:33 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-20 22:28:44
 */
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include "muduo/net/InetAddress.h"
#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/Buffer.h>
#include <iostream>

#include "TCPKeeper.hpp"
// #include "QueryProcessor.hpp"
// #include "MQProducer.hpp"

using namespace im;
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
        const char *ip = argv[1];
        uint16_t port = static_cast<uint16_t>(atoi(argv[2]));
        InetAddress listenAddr(ip, port);
        int threadCount = atoi(argv[3]);
        TCPKeeper keeper;
        keeper.start(ip, port, threadCount);
    }
    return 0;
}