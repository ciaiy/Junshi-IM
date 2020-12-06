/*
 * @Author: Qizhou 
 * @Date: 2020-10-12 00:01:57 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-12-03 03:20:01
 */
#include <iostream>
#include <thread>
#include "DefaultMQPushConsumer.h"
#include "../../common/CJsonObject.hpp"
#include "../../common/cJSON.h"
#include "Processor.hpp"
#include "../../common/myLog.h"

using namespace rocketmq;
using namespace std;
using im::common::logger;

namespace im
{

    class MessageListener : public MessageListenerConcurrently
    {
    private:
        Processor *processor = new Processor();

    public:
    
        ConsumeStatus consumeMessage(const std::vector<MQMessageExt> &msgs)
        {
            for (auto item = msgs.begin(); item != msgs.end(); item++)
            {
                logger->info(string("Received Message Topic:" + item->getTopic() + ", MsgId:" + item->getMsgId()) + item->getBody());
                processor->process(item->getBody());
            }
            return CONSUME_SUCCESS;
        }
    };
} // namespace im