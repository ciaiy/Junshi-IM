/*
 * @Author: Qizhou 
 * @Date: 2020-10-19 09:39:33 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-20 22:27:26
 */
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/Buffer.h>
#include <iostream>

#include "../../common/myLog.h"
#include "QueryProcessor.hpp"

using namespace muduo;
using namespace muduo::net;
using im::common::logger;

namespace im
{

    class QueryProcessor;

    class TCPKeeper
    {
    public:
        static const int HeaderLenth = 4;
        static const int DataMaxSize = 65534;

    public:
        TCPKeeper() = default;
        void start(const string &ip, uint16_t port, int threadNum);
        static void onConnection(const TcpConnectionPtr &conn);
        static void onClose(const TcpConnectionPtr &conn);
        static void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp);
    };
} // namespace im
