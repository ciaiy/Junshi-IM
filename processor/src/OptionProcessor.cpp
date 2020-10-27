/*
 * @Author: Qizhou 
 * @Date: 2020-10-22 17:54:50 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-22 18:38:31
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

OptionProcessor::OptionProcessor()
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
        login(optionQuery->getOptid(), optionQuery->getMessage());
        break;

    default:
        break;
    }
}

void OptionProcessor::login(string optid, string message)
{
    SQLResult sqlResult = sqlService.getUserInfo(optid);
    if (sqlResult.isSuccess())
    {
        CJsonObject userInfo = CJsonObject(CJsonObject(sqlResult.getData()).getItem(0));
        std::string userpasswd = userInfo.getString("user_passwd");
        if (message.compare(userpasswd) == 0)
        {
            logger->info("|OptionProcessor|login|optid = " + optid + " login success|");
            sqlService.userOnline(optid);
        }
        else
        {
            logger->info("|OptionProcessor|login|optid = " + optid + " login failed|");
        }
    }
    else
    {
        logger->warn("|OptionProcessor|login|optid = " + optid + ", errorInfo :" + sqlResult.result().ToString());
    }
}