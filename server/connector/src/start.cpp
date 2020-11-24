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
#include <DefaultMQPushConsumer.h>
#include "MessageListener.hpp"

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
        DefaultMQPushConsumer *consumer = new DefaultMQPushConsumer("GID_Connector");
        consumer->setNamesrvAddr("47.94.149.37:9876");
        //register your own listener here to handle the messages received.
        //请注册自定义侦听函数用来处理接收到的消息，并返回响应的处理结果。
        MessageListener *messageListener = new MessageListener();
        consumer->subscribe("SenderToConnector", "*");
        consumer->registerMessageListener(messageListener);
        //Start this consumer
        //准备工作完成，必须调用启动函数，才可以正常工作。
        // ********************************************
        // 1.确保订阅关系的设置在启动之前完成。
        // 2.确保相同 GID 下面的消费者的订阅关系一致。
        // *********************************************
        consumer->start();
        const char *ip = argv[1];
        uint16_t port = static_cast<uint16_t>(atoi(argv[2]));
        InetAddress listenAddr(ip, port);
        int threadCount = atoi(argv[3]);
        TCPKeeper keeper;
        keeper.start(ip, port, threadCount);
    }
    return 0;
}