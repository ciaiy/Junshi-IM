#ifndef _MQPRODUCER_H_
#define _MQPRODUCER_H_

#include <thread>
#include <DefaultMQProducer.h>

using namespace im;
using namespace rocketmq;

namespace im
{
    class MQProducer
    {
    public:
        // 后期均改为配置信息
        const string TopicName = "ConnectorToProcessor";
    public:
        static MQProducer *getInstance();
        DefaultMQProducer *producer;
        void produce(const string query);
    private:
        MQProducer();
    };

} // namespace im

#endif
