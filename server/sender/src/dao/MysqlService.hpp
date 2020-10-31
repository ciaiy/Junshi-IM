/*
 * @Author: Qizhou 
 * @Date: 2020-10-31 15:58:14 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-31 16:41:16
 */
#ifndef _MYSQLSERVICE_H_
#define _MYSQLSERVICE_H_

#include "MysqlSQLDriver.hpp"
#include <string>

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
            SQLResult checkUserOnline(const std::string &uid);
            SQLResult insertOfflineMsg(const string &uid, const string &type, const string &data);
        };

    } // namespace dao
} // namespace im
#endif
