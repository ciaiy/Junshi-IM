/*
 * @Author: Qizhou 
 * @Date: 2020-10-12 00:01:57 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-12 00:15:50
 */
#include <iostream>
#include <thread>
#include <DefaultMQPushConsumer.h>
#include "Sender.hpp"
#include "../../common/CJsonObject.hpp"
#include "../../common/cJSON.h"
#include "../../common/myLog.h"

using namespace rocketmq;
using namespace std;
using im::common::logger;

namespace im
{

    class MessageListener : public MessageListenerConcurrently
    {
    private:
        Sender *sender = new Sender();

    public:
        ConsumeStatus consumeMessage(const std::vector<MQMessageExt> &msgs)
        {
            for (auto item = msgs.begin(); item != msgs.end(); item++)
            {
                logger->info(string("Received Message Topic:" + item->getTopic() + ", MsgId:" + item->getMsgId()));
                sender->send(item->getBody());
            }
            return CONSUME_SUCCESS;
        }
    };
} // namespace im