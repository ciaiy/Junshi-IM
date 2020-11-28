/*
 * @Author: Qizhou 
 * @Date: 2020-11-25 16:15:25 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-11-25 16:28:46
 */
#ifndef _MESSAGESENDER_
#define _MESSAGESENDER_

#include "../../common/myLog.h"
#include <muduo/net/TcpConnection.h>

using namespace muduo;
using namespace muduo::net;

namespace im
{
    class MessageSender
    {
    public:
        void static sendResponse(const TcpConnectionPtr &conn, const string& msg);
        void static sendRequest(const TcpConnectionPtr &conn, const string& msg);
        void static send(const TcpConnectionPtr &conn, const string& msg);
    };
} // namespace im

#endif
