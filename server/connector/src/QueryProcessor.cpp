#include "QueryProcessor.hpp"
#include "../../common/CJsonObject.hpp"
#include "../../common/myLog.h"
#include "../../common/Exception.hpp"
#include "MQProducer.hpp"

using namespace im;
using namespace im::common;

QueryProcessor::ObjectCreator QueryProcessor::objectCreator;

QueryProcessor::QueryProcessor()
{
    logger->info("|QueryProcessor|Constructor complete|");
};

QueryProcessor *QueryProcessor::getInstance()
{
    static QueryProcessor processor;
    return &processor;
}

void QueryProcessor::receiveData(const TcpConnectionPtr &conn, std::string queryStr)
{
    CJsonObject queryJson(queryStr);
    try
    {
        int32_t dataAck = queryJson.getUInt32("dataAck");
        string authToken = queryJson.getString("authTokn");
        CJsonObject queryBody = queryJson.getCJsonObject("queryBody");
        uint32_t queryType = queryBody.getUInt32("type");
        // 在此检查数据是否安全，当mapper中没有该用户时，除非请求的类型为登录，否则其他的请求全部丢弃，并关闭该Connection
        if (userAuthCheck(conn, authToken, queryType))
        {

            logger->debug("|QueryProcessor|receiveData|dataAck" + to_string(dataAck));
            queryBody.Add("token", queryType == OPTION_LOGIN ? generateTempSign()
                                                             : boost::any_cast<string>(conn->getContext()));
            queryBody.Add("ext", queryType == OPTION_LOGIN ? authToken : "");
            MQProducer::getInstance()->produce(queryBody.ToString());
            conn->send(&dataAck, sizeof(int64_t));
        }
        else
        {
            throw Exception("userAuthCheck faild, Conneciton will close");
        }
    }
    catch (Exception ex)
    {
        logger->warn("|QueryProcessor|receiveData|" + string(ex.what()) + "|" + string(ex.stackTrace()) + "|");
    }
}

string QueryProcessor::generateTempSign()
{
    return to_string(time(nullptr));
}

bool QueryProcessor::userAuthCheck(const TcpConnectionPtr &conn, const string &authToken, const uint32_t type)
{
    boost::any context = conn->getContext();
    // 不为空的话，则校验其authToken是否和conn中的Context一致
    if (!context.empty())
    {
        std::string contextSign = boost::any_cast<string>(context);
        return contextSign.compare(authToken) == 0;
    }
    else
    {
        // 为空的话，则校验其是否为LOGIN
        return type == OPTION_LOGIN;
    }
}