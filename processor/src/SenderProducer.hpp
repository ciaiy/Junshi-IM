#ifndef _SENDERPRODUCER_H_
#define _SENDERPRODUCER_H_
#include <iostream>
#include <chrono>
#include <thread>
#include "DefaultMQProducer.h"
using namespace std;
using namespace rocketmq;

namespace im
{
    class SenderProducer
    {
    private:
        const string TopicName = "ProcessorToSender";
        DefaultMQProducer *producer;
        std::string threadId;

    public:
        SenderProducer();
        ~SenderProducer();
        void produce(const string &msg);
    };
} // namespace im

#endif