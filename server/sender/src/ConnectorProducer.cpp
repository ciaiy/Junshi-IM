#include "ConnectorProducer.hpp"
#include "../../common/myLog.h"
#include "../../common/CurrentThread.hpp"

using namespace im;
using namespace im::common;
using namespace rocketmq;

ConnectorProducer::ConnectorProducer()
{
    threadId = common::CurrentThread::getThreadIdOfString(this_thread::get_id());
    logger->debug("|ConnectorProducer|constructor|start|");
    producer = new DefaultMQProducer(threadId);
    producer->setNamesrvAddr("47.94.149.37:9876");
    producer->setSessionCredentials("AK", "SK", "ALIYUN");
    producer->start();
    logger->debug("|ConnectorProducer|constructor|complete|" + threadId + "|");
}

ConnectorProducer::~ConnectorProducer()
{
    producer->shutdown();
    delete producer;
}

void ConnectorProducer::produce(const string &msgBody)
{
    // 不安全，有可能produce失败
    MQMessage msg(TopicName, "HiTAG", msgBody);
    try
    {
        SendResult sendResult = producer->send(msg);
        logger->info("|ConnectorProducer|produce|Message ID: " + sendResult.getMsgId() + "|Message Body:" + msgBody + "|threadId : " + threadId + "|");
    }
    catch (MQException e)
    {
        logger->error("|ConnectorProducer|produce|produce error : ErrorCode: " + to_string(e.GetError()) + " Exception:" + e.what() + "| threadId : " + threadId + "|");
    }
}