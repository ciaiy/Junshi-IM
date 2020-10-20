#include "QueryProcessor.hpp"
#include "common/CJsonObject.hpp"
#include "common/myLog.h"
#include "common/Exception.hpp"

using namespace im;
using namespace im::common;

QueryProcessor *QueryProcessor::getInstance()
{
    static QueryProcessor processor;
    return &processor;
}

void QueryProcessor::receiveData(const TcpConnectionPtr &conn, string queryStr)
{
    CJsonObject queryJson(queryStr);
    try
    {
        int64_t dataAck = queryJson.getInt64("dataAck");
    }
    catch (Exception ex)
    {
        logger->warn("|QueryProcessor|receiveData|" + string(ex.what()) + "|" + string(ex.stackTrace()) + "|");
    }
}