/*
 * @Author: Qizhou 
 * @Date: 2020-10-02 23:37:51 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-04 09:44:16
 */
#include <iostream>

#include "RedisSQLDriver.hpp"
#include "../common/CJsonObject.hpp"
#include "../common/myLog.h"
#include "../common/config.hpp"
#include <mutex>

using namespace im::dao;
/*
 * 后期日志需要重新配置
 */
using im::common::logger;

RedisSQLDriver::RedisSQLDriver()
{
    logger->debug("|redisDriver|constructor|start|");
    CJsonObject config = CJsonObject(im::common::redisConfig);
    if(config.IsEmpty()) {
        logger->error("|redisDriver|constructor|parse redisConfig error|");
    }
    logger->debug("|redisDriver|constructor|" + config.ToFormattedString() + "|");
    SQLConn conn = SQLConn(config);
    logger->debug("|redisDriver|constructor|" + conn.toString() + "|");
    this->connect(conn);
}

RedisSQLDriver *RedisSQLDriver::getInstance()
{
    static RedisSQLDriver redisSQLDriver;
    return &redisSQLDriver;
}

SQLResult RedisSQLDriver::connect(SQLConn &conn)
{
    pRedisContext = (redisContext *)redisConnect(conn.ip().c_str(), atoi(conn.port().c_str()));
    if ((NULL == pRedisContext) || (pRedisContext->err))
    {
        if (pRedisContext)
        {
            logger->error("|redisDriver|" + string(pRedisContext->errstr) + "|");
        }
        else
        {
            logger->error("|redisDriver|connect error: can't allocate redis context.|");
        }
        exit(-1);
    }
    else
    {
        return SQLResult(0, "redis connect success");
    }
}

SQLResult RedisSQLDriver::disConnect()
{
    return SQLResult(0, "nil");
}

SQLResult RedisSQLDriver::opt(string query)
{
    //redisReply是Redis命令回复对象 redis返回的信息保存在redisReply对象中
    redisReply *pRedisReply = (redisReply *)redisCommand(pRedisContext, query.c_str()); //执行INFO命令
    //当多条Redis命令使用同一个redisReply对象时
    SQLResult result = SQLResult(
        (REDIS_REPLY_ERROR == pRedisReply->integer) ? REDIS_REPLY_ERROR : 0, string(pRedisReply->str));

    logger->info("|redisDriver|" + query + "|" + result.result().ToString() + "|");

    //每一次执行完Redis命令后需要清空redisReply 以免对下一次的Redis操作造成影响
    freeReplyObject(pRedisReply);
    return result;
}

SQLResult RedisSQLDriver::set(string key, string value)
{
    return opt("set " + key + " " + value);
}

SQLResult RedisSQLDriver::setWithExpire(string key, string value, string expireTime)
{
    return opt("set " + key + " " + value + " EX " + expireTime);
}
