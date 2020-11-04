#ifndef _CONNECTIONMAPPER_
#define _CONNECTIONMAPPER_
#include <map>
#include <string>
#include <muduo/net/TcpServer.h>
#include "../../common/Exception.hpp"

using namespace muduo::net;

namespace im
{
    class ConnectionMapper
    {
    private:
        std::map<std::string, const TcpConnectionPtr> mapper;

    public:
        std::string insertConnection(const TcpConnectionPtr &conn);
        bool findConnection(const std::string &key);
        const TcpConnectionPtr getConnection(const std::string &key);
         static ConnectionMapper *getInstance();
        DefaultConnectionMapper *mapper;
    
    public:
        // 辅助代理类
        struct ObjectCreator
        {
            ObjectCreator()
            {
                ConnectionMapper::getInstance();
            }
        };
        static ObjectCreator objectCreator;

    };

} // namespace im

#endif