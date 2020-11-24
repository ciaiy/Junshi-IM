#include "QueryProcessor.hpp"
#include "../../common/CJsonObject.hpp"
#include "../../common/myLog.h"
#include "../../common/Exception.hpp"
#include "MQProducer.hpp"
#include "ConnectionMapper.hpp"

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
        string dataAck = queryJson.getString("dataAck");
        CJsonObject context = queryJson.getCJsonObject("context");
        CJsonObject queryBody = queryJson.getCJsonObject("queryBody");
        // 在此检查数据是否安全，当mapper中没有该用户时，除非请求的类型为登录，否则其他的请求全部丢弃，并关闭该Connection
        if (userAuthCheckAndSet(conn, context.getString("authToken"), queryBody.getCJsonObject("queryInfo").getInt32("type")))
        {
            logger->debug("|QueryProcessor|receiveData|dataAck" + dataAck);
            // 临时加上ip + port
            context.Add("ip", "47.94.149.37");
            context.Add("port", "2333");
            CJsonObject query;
            query.Add("context", context);
            query.Add("queryBody", queryBody);
            query.Add("ext", "");
            MQProducer::getInstance()->produce(query.ToString());
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

bool QueryProcessor::userAuthCheckAndSet(const TcpConnectionPtr &conn, const string &authToken, const uint32_t type)
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
        if (type == OPTION_LOGIN)
        {
            try
            {
                conn->setContext(generateTempSign());
                ConnectionMapper::getInstance()->insertConnection(conn);
            }
            catch (Exception ex)
            {
                logger->info("|QueryProcessor|userAuthCheckAndSet| error " + string(ex.what()) + "|");
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}