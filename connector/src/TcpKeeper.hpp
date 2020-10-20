/*
 * @Author: Qizhou 
 * @Date: 2020-10-19 09:39:33 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-20 14:39:55
 */
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/Buffer.h>
#include <iostream>

#include "common/myLog.h"
#include "QueryProcessor.hpp"

using namespace muduo;
using namespace muduo::net;
using im::common::logger;
namespace im
{

    class TCPKeeper
    {
    public:
        static const int HeaderLenth = 4;
        static const int DataMaxSize = 65534;

        void onConnection(const TcpConnectionPtr &conn)
        {
            if (conn->connected())
            {
                logger->info("|TcpKeeper|onConnection|" + conn->getTcpInfoString() + "|");
                conn->setTcpNoDelay(true);
            }
        }

        void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp)
        {
            // 大于HeaderLenth 则进行读取
            while (buf->readableBytes() >= HeaderLenth)
            {
                const void *data = buf->peek();
                const int32_t dataLen = ntohl(*static_cast<const int32_t *>(data));
                if (dataLen > DataMaxSize || dataLen < 0)
                {
                    conn->shutdown();
                }
                else if (buf->readableBytes() >= dataLen)
                {
                    buf->retrieveInt32();
                    std::string query(buf->peek(), dataLen);
                    processor->receiveData(conn, query);
                    buf->retrieve(dataLen);
                }
                else
                {
                    break;
                }
            }
        }
        private:
            QueryProcessor *processor = QueryProcessor::getInstance();
    };
} // namespace im