/*
 * @Author: Qizhou 
 * @Date: 2020-10-02 23:38:08 
 * @Last Modified by:   Qizhou 
 * @Last Modified time: 2020-10-02 23:38:08 
 */
#ifndef _SQLCONN_H_
#define _SQLCONN_H_

#include <string>
#include <iostream>
#include "../common/CJsonObject.hpp"

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

        public:
            SQLConn(const CJsonObject &info)
            {
                info.Get("ip", _ip);
                info.Get("port", _port);
                info.Get("username", _username);
                info.Get("password", _password);
            }
            SQLConn(std::string ip,
                    std::string port,
                    std::string username,
                    std::string password) : _ip(ip),
                                            _port(port),
                                            _username(username),
                                            _password(password) {}
            std::string ip() { return _ip; }
            std::string port() { return _port; }
            std::string username() { return _username; }
            std::string password() { return _password; }
            std::string toString() {
                return "ip :" + _ip + ", port :" + _port + ", username :" + _username + ", password" + _password;  
            }
        };
    } // namespace dao

} // namespace im

#endif