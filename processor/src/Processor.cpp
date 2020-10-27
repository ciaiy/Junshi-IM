/*
 * @Author: Qizhou 
 * @Date: 2020-10-12 00:01:47 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-22 18:07:03
 */
#include "Processor.hpp"
#include "../../common/myLog.h"
#include "../../common/config.hpp"
#include "../../common/CJsonObject.hpp"
#include "entry/MessageQuery.hpp"
#include "OptionProcessor.hpp"

using namespace im;
using namespace im::common;
using namespace im::entry;

Processor::Processor()
{
    senderProducer = new SenderProducer();
    optionProcessor = new OptionProcessor(senderProducer);
    logger->info("|Processor|Constructor complete|");
}

void Processor::process(string msg)
{
    if (msg.empty())
    {
        logger->warn("|processor|process msg is null|");
    }
    else
    {
        CJsonObject query = CJsonObject(msg);
        if (query.IsEmpty())
        {
            logger->warn("|processor|process parse error|" + msg + "|");
        }
        string queryType;
        if (query.Get("queryType", queryType))
        {
            if (common::MESSAGE_QUREY.compare(queryType))
            {
                string messageQuery;
                if (query.Get("queryInfo", messageQuery))
                {
                    // MessageProcessor->process(createMessageQuery(messageQuery));
                }
                else
                {
                    logger->warn("|processor|process getQueryInfo error|" + msg + "|");
                }
            }
            else if (common::OPTION_QUERY.compare(queryType))
            {
                string optionQuery;
                if (query.Get("queryInfo", optionQuery))
                {
                    optionProcessor->process(optionQuery);
                }
                else
                {
                    logger->warn("|processor|process getQueryInfo error|" + msg + "|");
                }
            }
            else
            {
                logger->warn("|processor|process parseType error|" + msg + "|");
            }
        }
        else
        {
            logger->warn("|processor|process getType error|" + msg + "|");
        }
    }
}
