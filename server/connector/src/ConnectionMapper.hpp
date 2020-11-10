/*
 * @Author: Qizhou 
 * @Date: 2020-11-10 17:01:40 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-11-10 17:48:50
 */
#ifndef _CONNECTIONMAPPER_
#define _CONNECTIONMAPPER_
#include <map>
#include <mutex>
#include <stdlib>
#include <string>
#include <muduo/net/TcpServer.h>
#include "../../common/Exception.hpp"

using namespace muduo::net;

namespace im
{
    // todo : 线程不安全！！
    class ConnectionMapper
    {
    private:
        std::map<std::string, const TcpConnectionPtr> connectionMapper;
        mutex mtx;
    public:
        // 以下操作均为线程安全的
        bool findConnection(const std::string &key);
        const TcpConnectionPtr getConnection(const std::string &key);
        void deleteConneciton(const std::string key);
        std::string insertConnection(const TcpConnectionPtr &conn);

    public:
        static ConnectionMapper *getInstance();
        ConnectionMapper *mapper;

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