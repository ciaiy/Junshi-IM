#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
int main(int argc, char **argv)
{
    struct timeval timeout = {2, 0}; //2s的超时时间
    //redisContext是Redis操作对象
    redisContext *pRedisContext = (redisContext *)redisConnect("127.0.0.1", 6379);
    if ((NULL == pRedisContext) || (pRedisContext->err))
    {
        if (pRedisContext)
        {
            std::cout << "connect error:" << pRedisContext->errstr << std::endl;
        }
        else
        {
            std::cout << "connect error: can't allocate redis context." << std::endl;
        }
        return -1;
    }
    while (1)
    {
        std::string cmd = std::string();
        getline(std::cin, cmd);
        std::cout << "$" << cmd << std::endl;
        //redisReply是Redis命令回复对象 redis返回的信息保存在redisReply对象中
        redisReply *pRedisReply = (redisReply *)redisCommand(pRedisContext, cmd.c_str()); //执行INFO命令
        std::cout << pRedisReply->str << std::endl;
        //当多条Redis命令使用同一个redisReply对象时
        //每一次执行完Redis命令后需要清空redisReply 以免对下一次的Redis操作造成影响
        freeReplyObject(pRedisReply);
    }
    return 0;
}
