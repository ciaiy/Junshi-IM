/*
 * @Author: Qizhou 
 * @Date: 2020-10-23 10:08:21 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-31 16:45:50
 */
#ifndef _MYSQLSQLRRIVER_H_
#define _MYSQLSQLRRIVER_H_
#include <mysql/mysql.h>
#include <mutex>
#include <thread>
#include "SQLConn.hpp"
#include "SQLResult.hpp"
namespace im
{
    namespace dao
    {
        /*
            Mysql提供的api不支持线程并发, 需要给每个thread分配一个MysqlSQLDriver
        */
        class MysqlSQLDriver
        {
        private:
            MYSQL *sqlConn;
            void connect(SQLConn conn);
            static std::mutex init_lock;

        public:
            std::thread::id thisThread;
            MysqlSQLDriver();
            ~MysqlSQLDriver();

        public:
            SQLResult select(const std::string &query);
            SQLResult update(const std::string &query);
            SQLResult insert(const string &query);
        };
    } // namespace dao

} // namespace im

#endif