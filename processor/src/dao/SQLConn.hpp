/*
 * @Author: Qizhou 
 * @Date: 2020-10-02 23:38:08 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-23 10:38:09
 */
#ifndef _SQLCONN_H_
#define _SQLCONN_H_

#include <string>
#include <iostream>
#include "../../../common/CJsonObject.hpp"

using im::common::CJsonObject;

namespace im
{
    namespace dao
    {
        class SQLConn
        {
        private:
            std::string _ip;
            std::string _port;
            std::string _username;
            std::string _password;
            std::string _database;

        public:
            inline SQLConn(const CJsonObject &info)
            {
                _ip = info.getString("ip");
                _port = info.getString("port");
                _username = info.getString("username");
                _password = info.getString("password");
                _database = info.getString("database");
            }
            SQLConn(std::string ip,
                    std::string port,
                    std::string username,
                    std::string password) : _ip(ip),
                                            _port(port),
                                            _username(username),
                                            _password(password) {}
            inline std::string ip() { return _ip; }
            inline std::string port() { return _port; }
            inline std::string username() { return _username; }
            inline std::string password() { return _password; }
            inline std::string database() { return _database; }
            inline std::string toString()
            {
                return "ip :" + _ip + ", port :" + _port + ", username :" + _username + ", password" + _password + ", database" + _database;
            }
        };
    } // namespace dao

} // namespace im

#endif