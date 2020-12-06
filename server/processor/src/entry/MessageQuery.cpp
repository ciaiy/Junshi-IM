#include "MessageQuery.hpp"
#include "../../../common/CJsonObject.hpp"
#include "../../../common/Exception.hpp"
#include "../../../common/myLog.h"

using namespace im::common;
using namespace im::entry;

MessageQuery::MessageQuery(string queryStr)
{
    try
    {
        logger->debug("|MessageQuery|constructor start|");
        CJsonObject queryJson(queryStr);
        CJsonObject queryBody = queryJson.getCJsonObject("queryBody");
        CJsonObject queryInfo = queryBody.getCJsonObject("queryInfo");
        CJsonObject messageInfo(queryInfo.getString("message"));
        context = queryJson.getCJsonObject("context");
        uid = messageInfo.getString("uid");
        cid = messageInfo.getString("cid");
        msgId = messageInfo.getString("msgId");
        message = messageInfo.getString("message");
        type = messageInfo.getInt32("type");
        ext = messageInfo.getString("ext");
        sourceName = messageInfo.getString("sourceName");
        sourceType = messageInfo.getInt32("sourceType");
        sourceUid = messageInfo.getString("sourceUid");
    }
    catch (Exception ex)
    {
        logger->info("|MessageQuery|constructor|error : " + string(ex.what()) + "|");
    }
}
