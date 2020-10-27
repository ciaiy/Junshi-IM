#ifndef _MYSQLSERVICE_H_
#define _MYSQLSERVICE_H_

#include "MysqlSQLDriver.hpp"
namespace im
{
    namespace dao
    {
        class MysqlService
        {
        private:
            /* data */
            MysqlSQLDriver sqlDriver;
            std::thread::id thisThread;
        public:
        MysqlService();
            ~MysqlService() = default;
            SQLResult getUserInfo(const std::string& uid);
            SQLResult userOnline(const std::string& uid);
        };

    } // namespace dao
} // namespace im
#endif
