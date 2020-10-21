#ifndef _QUERY_PROCESSOR_H_
#define _QUERY_PROCESSOR_H_

#include "../../common/SingletonPattern.hpp"
#include "MQProducer.hpp"

#include <muduo/net/TcpConnection.h>

using im::common::SingtonPattern;
using std::string;
using namespace muduo;
using namespace muduo::net;

namespace im
{
    class QueryProcessor : SingtonPattern
    {
    public:
        static QueryProcessor *getInstance();

    private:
        MQProducer *producer;
        QueryProcessor();

    public:
        void receiveData(const TcpConnectionPtr &conn, std::string query);

    public:
        // 辅助代理类
        struct ObjectCreator
        {
            ObjectCreator()
            {
                QueryProcessor::getInstance();
            }
        };
        static ObjectCreator objectCreator;
    };

} // namespace im
#endif
