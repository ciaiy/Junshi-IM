#include "MQProducer.hpp"
#include "../../common/myLog.h"

using namespace im;

using im::common::logger;
using rocketmq::SendStatus;

MQProducer *MQProducer::getInstance()
{
     static MQProducer producer;
    return &producer;
}

void MQProducer::produce(const std::string query)
{
    // 不安全，有可能produce失败
    MQMessage msg(MQProducer::TopicName, "HiTAG", query);
    try
    {
        SendResult sendResult = producer->send(msg);
        logger->info("|MQProducer|produce|Message ID: " + sendResult.getMsgId() + "|");
    }
    catch (MQException e)
    {
        std::cout << "ErrorCode: " << e.GetError() << " Exception:" << e.what() << std::endl;
    }
}

MQProducer::MQProducer()
{
    producer = new DefaultMQProducer("qizhouTestProducerGroup");
    producer->setNamesrvAddr("47.94.149.37:9876");

    producer->setSessionCredentials("AK", "SK", "ALIYUN");

    //请确保参数设置完成之后启动 Producer。
    producer->start();
    logger->info("|MQProducer|constructor|producer start|");
}