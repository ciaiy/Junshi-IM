#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include "muduo/net/InetAddress.h"
#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/Buffer.h>
#include <iostream>

using namespace muduo::net;
using namespace std;
using namespace std;

void onConnection(const TcpConnectionPtr &conn)
{
    if (conn->connected())
    {
        std::cout <<"xinlianjie"<<std::endl;
    }
}

void onMessage(const TcpConnectionPtr &conn, muduo::net::Buffer *buffer, muduo::Timestamp) {
    std::cout << "start readable : "<< buffer->readableBytes()  << "size" << sizeof(int32_t)<< std::endl;
	while(buffer->readableBytes() >= 4) {
        int length = buffer->peekInt32();
        cout << "length : " << length << endl;
        buffer->retrieveInt32();
        cout << "readable : " << buffer->readableBytes() << endl;
    }
   
}

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
        int threadCount = 4;
        EventLoop loop;
        TcpServer server(&loop, listenAddr, "TcpKeeper");
        server.setConnectionCallback(onConnection);
        server.setMessageCallback(onMessage);
        server.start();
        loop.loop();
        while(1){}
    }
    return 0;
}
