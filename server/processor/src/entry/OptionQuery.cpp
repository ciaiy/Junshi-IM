#include "OptionQuery.hpp"
#include "../../../common/CJsonObject.hpp"
#include "../../../common/Exception.hpp"
#include "../../../common/myLog.h"

using namespace im::common;
using namespace im::entry;

OptionQuery::OptionQuery(string queryStr)
{
    try{
    CJsonObject queryJson(queryStr);
    CJsonObject queryInfo = queryJson.getCJsonObject("queryInfo");
    context = queryJson.getCJsonObject("context").ToString();
    uid = queryInfo.getString("uid");
    cid = queryInfo.getString("cid");
    optid = queryInfo.getString("optid");
    type = queryInfo.getInt32("type");
    message = queryInfo.getString("message");
    ext = queryInfo.getString("ext");
    }catch(Exception ex) {
        logger->info("|OptionQuery|constructor|error  = " + string(ex.what()) + "|");
    }
}
