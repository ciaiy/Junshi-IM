#ifndef _SERVERPROCESSOR_
#define _SERVERPROCESSOR_

#include "../../common/SingletonPattern.hpp"
#include "../../common/Exception.hpp"
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

    public:
        void receiveData(const TcpConnectionPtr &conn, const std::string msg) throw(common::Exception);
    };
} // namespace im

#endif
