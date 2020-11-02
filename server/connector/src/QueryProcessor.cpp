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
        logger->debug("|QueryProcessor|receiveData|dataAck" + to_string(dataAck));
        MQProducer::getInstance()->produce(queryJson.getCJsonObject("queryBody").ToString());
        conn->send(&dataAck, sizeof(int64_t));
    }
    catch (Exception ex)
    {
        logger->warn("|QueryProcessor|receiveData|" + string(ex.what()) + "|" + string(ex.stackTrace()) + "|");
    }
}