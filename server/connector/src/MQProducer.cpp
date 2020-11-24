#include "MQProducer.hpp"
#include "../../common/myLog.h"

using namespace im;

using im::common::logger;
using rocketmq::SendStatus;

MQProducer::ObjectCreator MQProducer::objectCreator;

MQProducer *MQProducer::getInstance()
{
    static MQProducer producer;
    return &producer;
}

void MQProducer::produce(const std::string query)
{
    // 不安全，有可能produce失败
    MQMessage msg("ConnectorToProcessor", "HiTAG", query);
    try
    {
        SendResult sendResult = producer->send(msg);
        logger->info("|MQProducer|produce|Message ID: " + sendResult.getMsgId() + "|Message Body:" + query + "|");
    }
    catch (MQException e)
    {
        logger->error("|MQProducer|produce|produce error : ErrorCode: " + to_string(e.GetError()) + " Exception:" + e.what());
    }
}

MQProducer::MQProducer()
{
    logger->debug("|MQProducer|constructor|");
    producer = new DefaultMQProducer("GID_Connector");
    producer->setNamesrvAddr("47.94.149.37:9876");

    //请确保参数设置完成之后启动 Producer。
    producer->start();
    logger->info("|MQProducer|constructor complete|");
}