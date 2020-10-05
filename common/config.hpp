#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

namespace im
{
    namespace common
    {
        // 后期替换掉这种写法
        static std::string redisConfig = "{\"ip\": \"127.0.0.1\",\"port\": \"6379\",\"username\": \"null\", \"password\": \"null\"}";
    } // namespace common
} // namespace im

#endif
