#include "SenderProducer.hpp"
#include "../../common/myLog.h"
#include "../../common/CurrentThread.hpp"

using namespace im;
using namespace im::common;
using namespace rocketmq;

SenderProducer::SenderProducer()
{
    threadId = common::CurrentThread::getThreadIdOfString(this_thread::get_id());
    logger->debug("|SenderProducer|constructor|start|");
    producer = new DefaultMQProducer(threadId);
    producer->setNamesrvAddr("47.94.149.37:9876");
    producer->setSessionCredentials("AK", "SK", "ALIYUN");
    producer->start();
    logger->debug("|SenderProducer|constructor|complete|" + threadId + "|");
}

SenderProducer::~SenderProducer()
{
    producer->shutdown();
    delete producer;
}

void SenderProducer::produce(const string &msgBody)
{
    // 不安全，有可能produce失败
    MQMessage msg(TopicName, "HiTAG", msgBody);
    try
    {
        SendResult sendResult = producer->send(msg);
        logger->info("|SenderProducer|produce|Message ID: " + sendResult.getMsgId() + "|Message Body:" + msgBody + "|threadId : " + threadId + "|");
    }
    catch (MQException e)
    {
        logger->error("|SenderProducer|produce|produce error : ErrorCode: " + to_string(e.GetError()) + " Exception:" + e.what() + "| threadId : " + threadId + "|");
    }
}