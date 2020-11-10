/*
 * @Author: Qizhou 
 * @Date: 2020-11-10 17:09:55 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-11-10 17:54:55
 */
#ifndef _PROCESSOR_
#define _PROCESSOR_

#include "../../common/SingletonPattern.hpp"
#include "../../common/myLog.h"
#include "QueryProcessor.hpp"
#include "ServerProcessor.hpp"

#include <muduo/net/TcpConnection.h>
#include <string>

using namespace muduo::net;
using namespace im::common;

namespace im
{
    class Processor : SingtonPattern
    {
        // todo : 单例模式
    private:
        QueryProcessor *queryProcessor;
        ServerProcessor *serverProcessor;
        const string ORIGIN_CLIENT = "cient";
        const string ORIGIN_SERVER = "server";
    public:
        // 仅做参数校验，随后会分发至不同的processor
        void receiveData(const TcpConnectionPtr &conn, const std::string &msg);
        Processor();
    };

} // namespace im

#endif