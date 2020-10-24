// /*
//  * @Author: Qizhou 
//  * @Date: 2020-10-02 23:38:03 
//  * @Last Modified by: Qizhou
//  * @Last Modified time: 2020-10-23 10:09:27
//  */
// #ifndef _REDISSQLDRIVER_H_
// #define _REDISSQLDRIVER_H_

// #include <hiredis/hiredis.h>
// #include <string.h>

// #include "SQLResult.hpp"
// #include "SQLConn.hpp"
// #include "../common/SingletonPattern.hpp"

// using im::dao::SQLConn;
// using im::dao::SQLResult;
// using im::common::SingtonPattern;

// namespace im
// {
//     namespace dao
//     {
//         class RedisSQLDriver : SingtonPattern
//         {
//         private:
//             redisContext *pRedisContext;
//             virtual SQLResult opt(std::string query);
//             virtual SQLResult connect(SQLConn &conn);
//             RedisSQLDriver();
//         public:
//             static RedisSQLDriver *getInstance();
//             virtual SQLResult disConnect();
//             SQLResult set(std::string key, std::string value);
//             SQLResult setWithExpire(std::string key, std::string value, std::string expireTime);
//         };

//     } // namespace dao
// } // namespace im

// #endif