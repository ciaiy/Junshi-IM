#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

namespace im
{
    namespace common
    {
        // 后期替换掉这种写法
        static const std::string redisConfig = "{\"ip\": \"127.0.0.1\",\"port\": \"6379\",\"username\": \"null\", \"password\": \"null\"}";
        static const std::string MESSAGE_QUREY = "messageQuery";
        static const std::string OPTION_QUERY = "optionQuery";

    } // namespace common
} // namespace im

#endif