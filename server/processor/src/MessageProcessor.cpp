/*
 * @Author: Qizhou 
 * @Date: 2020-12-03 03:18:29 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-12-03 03:51:58
 */

#include "MessageProcessor.hpp"
#include "../../common/myLog.h"
#include "../../common/Exception.hpp"
#include "entry/OptionQuery.hpp"
#include "dao/MysqlService.hpp"
#include "../../common/CurrentThread.hpp"
#include "dao/SQLResult.hpp"

using namespace im;
using namespace im::common;
using namespace im::entry;
using namespace im::dao;

MessageProcessor::MessageProcessor(SenderProducer *senderProducer) : senderProducer(senderProducer)
{
    logger->info("|MessageProcessor|Constructor complete|");
}

void MessageProcessor::process(MessageQuery query)
{
    // todo 加入Cid校验等功能
    SQLResult sqlResult = sqlService.insertMsg(query);
    CJsonObject msg;
    msg.Add("optid", query.getUid());
    msg.Add("type", "MSG_ACK");
    msg.Add("mustDeliver", false);
    msg.Add("context", query.getContext());
    CJsonObject data;
    if (sqlResult.isSuccess())
    {
        data.Add("msgAck", query.getMsgId());
        data.Add("status", 1);
        data.Add("cid", query.getCid());
        msg.Add("data", data);
        senderProducer->produce(msg.ToString());
    }
    else
    {
        // todo 目前drop
    }
}