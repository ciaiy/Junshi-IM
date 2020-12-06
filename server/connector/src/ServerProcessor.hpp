#ifndef _SERVERPROCESSOR_
#define _SERVERPROCESSOR_

#include "../../common/SingletonPattern.hpp"
#include "../../common/Exception.hpp"
#include "../../common/CJsonObject.hpp"
#include "ConnectionMapper.hpp"
#include <muduo/net/TcpConnection.h>

using namespace muduo::net;
using namespace im::common;

namespace im
{
    // todo : 完成单例
    class ServerProcessor : SingtonPattern
    {
    private:
        ConnectionMapper *mapper;
        ServerProcessor();

    public:
        void receiveData(const std::string msg);
        void refreshConnection(const TcpConnectionPtr &conn, CJsonObject context);

    public:
        static ServerProcessor *getInstance();

    public:
        // 辅助代理类
        struct ObjectCreator
        {
            ObjectCreator()
            {
                ServerProcessor::getInstance();
            }
        };
        static ObjectCreator objectCreator;
    };
} // namespace im

#endif
