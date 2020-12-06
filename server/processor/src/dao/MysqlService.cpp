#include "MysqlService.hpp"
#include "../../../common/myLog.h"

using namespace im;
using namespace im::common;
using namespace im::dao;

MysqlService::MysqlService()
{
    logger->info("|MysqlService|constructor|complete|");
}
/**
 *  获取allUser表中所有信息 
 */
SQLResult MysqlService::getUserInfo(const std::string &uid)
{
    logger->debug("|MysqlService|getUserInfo|start|");
    string query = "select * from allUser where account = " + uid;
    return sqlDriver.select(query);
}

/**
 *  更新allUser表中某个用户的在线状态位
 */
SQLResult MysqlService::userOnline(const std::string &uid)
{
    string query = "update allUser set onlineState = 1 where account = " + uid;
    return sqlDriver.update(query);
}

/**
 *  插入一条消息数据 
 */
SQLResult MysqlService::insertMsg(MessageQuery messageQuery)
{
    cout << messageQuery.getSourceName() << "|||" << to_string(messageQuery.getSourceType()) << endl;
    string query = "insert into msg (msgid, cid, message, type, sourceName, sourceType, sourceUid, createTime) values ('" +
                   messageQuery.getMsgId() + "','" +
                   messageQuery.getCid() + "','" +
                   messageQuery.getMessage() + "'," +
                   to_string(messageQuery.getType()) + ",'" +
                   messageQuery.getSourceName() + "'," +
                   to_string(messageQuery.getSourceType()) + "," +
                   messageQuery.getSourceUid() + ",'" +
                   to_string(time(0)) + "')";

    return sqlDriver.insert(query);
}