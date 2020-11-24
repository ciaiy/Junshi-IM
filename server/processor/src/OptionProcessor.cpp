/*
 * @Author: Qizhou 
 * @Date: 2020-10-22 17:54:50 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-31 16:39:39
 */
#include "OptionProcessor.hpp"
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

OptionProcessor::OptionProcessor(SenderProducer *senderProducer) : senderProducer(senderProducer)
{
    logger->info("|OptionProcessor|Constructor complete|");
}

void OptionProcessor::process(string query)
{
    logger->info("|OptionProcessor|process|query :" + query + "|");
    OptionQuery *optionQuery;
    try
    {
        optionQuery = new OptionQuery(query);
    }
    catch (Exception ex)
    {
        logger->warn("|OptionProcessor|process|" + string(ex.what()) + "|" + ex.stackTrace() + "|");
    }
    dispatch(optionQuery);
    delete optionQuery;
}

void OptionProcessor::dispatch(OptionQuery *optionQuery)
{
    switch (optionQuery->getType())
    {
    case OptionQuery::Type::LOGIN:
        login(optionQuery->getOptid(), optionQuery->getMessage(), optionQuery->getContext());
        break;

    default:
        break;
    }
}

void OptionProcessor::login(string optid, string message, string context)
{
    SQLResult sqlResult = sqlService.getUserInfo(optid);
    // 检查SQL 出错
    if (!sqlResult.isSuccess())
    {
        logger->warn("|OptionProcessor|login|optid = " + optid + ", errorInfo :" + sqlResult.result().ToString());
    }
    else
    {
        logger->debug("|OptionProcessor|login|sqlResult = " + sqlResult.getData() + "|");
        // 登录账号不存在
        if (sqlResult.getData().compare("") == 0)
        {
            logger->info("|OptionProcessor|login|optid = " + optid + " user not exist|");
        }
        else
        {
            // 校验密码是否正确
            CJsonObject result(sqlResult.getData());
            CJsonObject userInfo = CJsonObject(result[0]);
            std::string userpasswd = userInfo.getString("user_passwd");
            if (message.compare(userpasswd) == 0)
            {
                logger->info("|OptionProcessor|login|optid = " + optid + " login success|");
                sqlService.userOnline(optid);
                CJsonObject msg;
                msg.Add("optid", optid);
                msg.Add("type", "USER_ONLINE");
                CJsonObject data;
                data.Add("userInfo", userInfo);
                msg.Add("data", data);
                msg.Add("mustDeliver", true);
                msg.Add("context", CJsonObject(context));
                senderProducer->produce(msg.ToString());
                logger->info("|OptionProcessor|login|login success| optid = " + optid + "|");
            }else {
                logger->info("|OptionProcessor|login|login failed| optid = " +  optid + "|password wrong|");
            }
        }
    }
}