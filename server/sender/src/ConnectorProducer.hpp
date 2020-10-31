#ifndef _CONNECTORPRODUCER_H_
#define _CONNECTORPRODUCER_H_
#include <iostream>
#include <chrono>
#include <thread>
#include "DefaultMQProducer.h"
using namespace std;
using namespace rocketmq;

namespace im
{
    class ConnectorProducer
    {
    private:
        // todo: 后期将会去掉这个消息中间件，使用TCP直连+代理层的方式来解决接入层拓展问题
        const string TopicName = "SenderToConnector";
        DefaultMQProducer *producer;
        std::string threadId;

    public:
        ConnectorProducer();
        ~ConnectorProducer();
        void produce(const string &msg);
    };
} // namespace im

#endif