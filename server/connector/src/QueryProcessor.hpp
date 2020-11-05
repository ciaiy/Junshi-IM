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
        const uint32_t OPTION_LOGIN = 1;

    private:
        MQProducer *producer;
        QueryProcessor();
        bool userAuthCheck(const TcpConnectionPtr &conn, const string &authToken, const uint32_t type);
        string generateTempSign();
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
