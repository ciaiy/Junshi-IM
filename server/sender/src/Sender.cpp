#include "Sender.hpp"
#include "dao/MysqlService.hpp"
#include "../../common/myLog.h"
#include "../../common/Exception.hpp"
#include "../../common/CJsonObject.hpp"

using std::string;
using namespace im;
using namespace im::common;

void Sender::send(const std::string &msg)
{
    try
    {
        CJsonObject msgJson(msg);
        std::string uid = msgJson.getString("optid");
        std::string onlineState = CJsonObject(CJsonObject(sqlService.checkUserOnline(uid).getData())[0]).getString("onlineState");
        logger->debug("|Sender|send|onlineStatus = " + onlineState + "|");
        logger->debug("|Sender|send|msgJson=" + msgJson.ToString() + "|");
        int mustDeliver = msgJson.getInt32("mustDeliver");
        logger->info("|Sender|send|mustDeliver = " + to_string(mustDeliver) + "|");
        if (onlineState.compare(ONLINE_STATUS) == 0)
        {
            logger->info("|Sender|send|useronline| optid = " + uid + "|");
            std::string type = msgJson.getString("type");
            CJsonObject data = msgJson.getCJsonObject("data");
            CJsonObject context = msgJson.getCJsonObject("context");
            CJsonObject resultData;
            resultData.Add("context", context);
            resultData.Add("type", type);
            resultData.Add("optid", uid);
            resultData.Add("data", data);
            resultData.Add("sendId", "");
            resultData.Add("cid", "");
            producer.produce(resultData.ToString());
        }
        else if (mustDeliver == DELIVER)
        {
            logger->info("|Sender|send|user offline and need deliver|optid = " + uid + "|");
            std::string data = msgJson.getString("data");
            std::string type = msgJson.getString("type");
            auto sqlResult = sqlService.insertOfflineMsg(uid, type, data);
            if (!sqlResult.isSuccess())
            {
                // do something...
                // todo : 后期加入循环写入
                logger->info("|Sender|send|insertofflineMsg error|" + sqlResult.result().ToString() + "|");
            }
        }
        else
        {
            // else drop data
            logger->info("|Sender|send|user offline and dont need deliver|optid = " + uid + "|");
        }
    }
    catch (Exception ex)
    {
        logger->info("|Sender|send|error|" + string(ex.what()) + "|");
    }
}