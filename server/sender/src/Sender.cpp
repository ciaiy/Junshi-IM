#include "Sender.hpp"
#include "dao/MysqlService.hpp"
#include "../../common/CJsonObject.hpp"

using namespace im;
using namespace im::common;

void Sender::send(const std::string &msg)
{
    CJsonObject msgJson(msg);
    std::string uid = msgJson.getString("optid");
    std::string onlineState = CJsonObject(CJsonObject(sqlService.checkUserOnline(uid).getData()).getItem(0)).getString("onlineState");
    bool mustDeliver = msgJson.getBool("mustDeliver");
    if (onlineState.compare(ONLINE_STATUS) == 0)
    {
        std::string type = msgJson.getString("type");
        CJsonObject data = msgJson.getCJsonObject("data");
        CJsonObject resultData;
        resultData.Add("type", type);
        resultData.Add("optid", uid);
        resultData.Add("data", data);
        resultData.Add("sendId", "");
        resultData.Add("cid", "");
        producer.produce(resultData.ToString());
    }
    else if (mustDeliver)
    {
        std::string data = msgJson.getString("data");
        std::string type = msgJson.getString("type");
        if (!sqlService.insertOfflineMsg(uid, type, data).isSuccess())
        {
            // do something...
            // todo : 后期加入循环写入
        }
    }
    // else drop data
}