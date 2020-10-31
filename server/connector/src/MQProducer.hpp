#ifndef _MQPRODUCER_H_
#define _MQPRODUCER_H_

#include <thread>
#include <DefaultMQProducer.h>

using namespace rocketmq;

namespace im
{
    class MQProducer
    {
    public:
        // 后期均改为配置信息
        const std::string TopicName = "ConnectorToProcessor";

    public:
        static MQProducer *getInstance();
        DefaultMQProducer *producer;
        void produce(const std::string query);

    private:
        MQProducer();

    public:
        // 辅助代理类
        struct ObjectCreator
        {
            ObjectCreator()
            {
                MQProducer::getInstance();
            }
        };
        static ObjectCreator objectCreator;
    }; 

} // namespace im

#endif
