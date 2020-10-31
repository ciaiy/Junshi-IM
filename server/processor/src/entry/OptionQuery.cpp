#include "OptionQuery.hpp"
#include "../../../common/CJsonObject.hpp"
#include "../../../common/Exception.hpp"
#include "../../../common/myLog.h"

using namespace im::common;
using namespace im::entry;

OptionQuery::OptionQuery(string queryStr)
{
    CJsonObject queryJson(queryStr);

    uid = queryJson.getString("uid");
    cid = queryJson.getString("cid");
    optid = queryJson.getString("optid");
    type = queryJson.getInt32("type");
    message = queryJson.getString("message");
    ext = queryJson.getString("ext");
}
