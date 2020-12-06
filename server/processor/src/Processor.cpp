/*
 * @Author: Qizhou 
 * @Date: 2020-10-12 00:01:47 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-12-03 03:40:27
 */
#include "Processor.hpp"
#include "../../common/myLog.h"
#include "../../common/config.hpp"
#include "../../common/Exception.hpp"
#include "../../common/CJsonObject.hpp"
#include "entry/MessageQuery.hpp"
#include "OptionProcessor.hpp"
#include "MessageProcessor.hpp"

using namespace im;
using namespace im::common;
using namespace im::entry;

Processor::Processor()
{
    senderProducer = new SenderProducer();
    optionProcessor = new OptionProcessor(senderProducer);
    messageProcessor = new MessageProcessor(senderProducer);
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
        try
        {
            CJsonObject query = CJsonObject(msg);
            CJsonObject queryBody = query.getCJsonObject("queryBody");
            if (query.IsEmpty())
            {
                logger->warn("|processor|process parse error|" + msg + "|");
            }
            string queryType = queryBody.getString("queryType");
            if (common::MESSAGE_QUREY.compare(queryType) == 0)
            {

                messageProcessor->process(MessageQuery(msg));
            }
            else if (common::OPTION_QUERY.compare(queryType) == 0)
            {
                CJsonObject queryInfo = queryBody.getCJsonObject("queryInfo");
                CJsonObject context = query.getCJsonObject("context");
                CJsonObject optionQuery;
                optionQuery.Add("context", context);
                optionQuery.Add("queryInfo", queryInfo);
                optionQuery.Add("ext", "");
                optionProcessor->process(optionQuery.ToString());
            }
        }
        catch (Exception ex)
        {
            logger->warn("|processor|process error|" + string(ex.what()) + "|");
        }
    }
}