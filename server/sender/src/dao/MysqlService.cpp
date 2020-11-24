/*
 * @Author: Qizhou 
 * @Date: 2020-10-31 15:58:12 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-31 16:42:55
 */
#include "MysqlService.hpp"
#include "../../../common/myLog.h"
#include <string>
using namespace im;
using namespace im::common;
using namespace im::dao;
using std::string;
MysqlService::MysqlService()
{
    logger->info("|MysqlService|constructor|complete|");
}
/**
 *  获取allUser表中所有信息 
 */
SQLResult MysqlService::checkUserOnline(const string &uid)
{
    string query = "select onlineState from allUser where account = " + uid;
    // select(query);
    return sqlDriver.select(query);
}

SQLResult MysqlService::insertOfflineMsg(const string &uid, const string &type, const string &data)
{
    string query = "insert into offlineMsg(account, msgType, msgData) value (" + uid + ", " + type + ", " + data + ")";
    return sqlDriver.insert(query);
}