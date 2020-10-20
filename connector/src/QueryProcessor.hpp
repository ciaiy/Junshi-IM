#ifndef _QUERY_PROCESSOR_H_
#define _QUERY_PROCESSOR_H_

#include "common/SingletonPattern.hpp"
#include "MQProducer.hpp"

#include <muduo/net/TcpConnection.h>

using im::common::SingtonPattern;

using namespace muduo;
using namespace muduo::net;
namespace im
{
    class QueryProcessor : SingtonPattern
    {
    public:
        static QueryProcessor *getInstance();

    private:
        MQProducer *producer = MQProducer::getInstance();

    public:
        void receiveData(const TcpConnectionPtr &conn, string query);

    private:
        QueryProcessor() = default;
    };

} // namespace im
#endif
