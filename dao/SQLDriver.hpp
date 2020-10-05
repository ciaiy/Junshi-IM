/*
 * @Author: Qizhou 
 * @Date: 2020-10-02 23:38:14 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-03 10:18:46
 */
#ifndef _SQLDRIVER_H_
#define _SQLDRIVER_H_

#include <string>
#include "SQLConn.hpp"
#include "SQLResult.hpp"

namespace im
{
    namespace dao
    {

        using im::dao::SQLConn;
        using im::dao::SQLResult;

        /**
         * SQLDriver为抽象父类，MySQLDriver/RedisDriver均需继承
         */
        class SQLDriver
        {

        public:
            virtual SQLResult connect(SQLConn &conn) = 0;
            virtual SQLResult disConnect() = 0;
            virtual SQLResult add(std::string query) = 0;
            virtual SQLResult del(std::string query) = 0;
            virtual SQLResult mod(std::string query) = 0;
            virtual SQLResult get(std::string query) = 0;
            virtual SQLResult opt(std::string query) = 0;
        };
    } // namespace dao
} // namespace im

#endif