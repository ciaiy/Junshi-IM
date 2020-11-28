#include "MessageSender.hpp"
#include "../../common/myLog.h"
#include "../../common/CJsonObject.hpp"

using namespace im::common;
using namespace im;

void MessageSender::send(const TcpConnectionPtr &conn, const string &msg)
{
    int dataLen = msg.length();
    logger->info("|MessageSender|sendResponse|dataLen = " + to_string(dataLen) + "|data = " + msg + "|");
    char data[sizeof(int) + dataLen];
    *(int *)data = dataLen;
    strcpy(data + sizeof(int), msg.c_str());
    conn->send(data, dataLen + sizeof(int));
}

void MessageSender::sendResponse(const TcpConnectionPtr &conn, const string &msg)
{
    CJsonObject msgJson;
    msgJson.Add("dataType", "Response");
    msgJson.Add("dataAck", msg);
    send(conn, msgJson.ToString());
}

void MessageSender::sendRequest(const TcpConnectionPtr &conn, const string &msg) {
    // todo: 后期加入messageMap
    send(conn, msg);
}