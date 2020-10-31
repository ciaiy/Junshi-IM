#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

namespace im
{
    namespace common
    {
        /**
         * todo: 后期替换掉这种写法
         */
        static const int ThreadNum = 2;
        static const std::string redisConfig = "{\"ip\": \"127.0.0.1\",\"port\": \"6379\",\"username\": \"null\", \"password\": \"null\",\"database\":\"null\" }";
        static const std::string MysqlConfig = "{\"ip\": \"127.0.0.1\",\"port\": \"3306\",\"username\": \"root\", \"password\": \"132134\", \"database\":\"im\"}";
        static const std::string MESSAGE_QUREY = "messageQuery";
        static const std::string OPTION_QUERY = "optionQuery";

    } // namespace common
} // namespace im

#endif
