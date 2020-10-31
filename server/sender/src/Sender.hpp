#ifndef _SENDER_H_
#define _SENDER_H_

#include <iostream>
#include "dao/MysqlService.hpp"
#include "ConnectorProducer.hpp"
namespace im
{
    class Sender
    {
    public:
        void send(const std::string &msg);
        const std::string ONLINE_STATUS = "1";
        const std::string OFFLINE_STATUS = "0";
    private:
        dao::MysqlService sqlService;
        ConnectorProducer producer;
    };
} // namespace im

#endif