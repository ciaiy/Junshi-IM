/*
 * @Author: Qizhou 
 * @Date: 2020-10-12 00:01:47 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-12 00:40:42
 */
#include "Processor.hpp"
#include "common/myLog.h"
#include "common/config.hpp"
#include "common/CJsonObject.hpp"
#include "entry/MessageQuery.hpp"

using namespace im;
using im::common::CJsonObject;
using im::common::logger;
using im::entry::MessageQuery;

namespace im
{
    Processor *Processor::getInstance()
    {
        static Processor processor;
        return &processor;
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
                        MessageProcessor->process(createMessageQuery(messageQuery));
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
                        optionProcessor->process(createOptionQuery(optionQuery));
                    }
                    else
                    {
                        logger->warn("|processor|process getQueryInfo error|" + msg + "|");
                    }
                }
                else
                {
                    logger->warn("|processor|process paeseType error|" + msg + "|");
                }
            }
            else
            {
                logger->warn("|processor|process getType error|" + msg + "|");
            }
        }
    }

    void createMessageQuery(string queryBody) {

    }
} // namespace im
