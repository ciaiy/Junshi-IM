#include "MysqlService.hpp"
#include "../../../common/myLog.h"
using namespace im;
using namespace im::common;
using namespace im::dao;

MysqlService::MysqlService() {
    logger->info("|MysqlService|constructor|complete|");
}
/**
 *  获取allUser表中所有信息 
 */
SQLResult MysqlService::getUserInfo(const std::string& uid) {
    logger->debug("|MysqlService|getUserInfo|start|");
    string query = "select * from allUser where account = " + uid;
    return sqlDriver.select(query);
}

/**
 *  更新allUser表中某个用户的在线状态位
 */ 
SQLResult MysqlService::userOnline(const std::string& uid) {
    string query = "update allUser set onlineState = 1 where account = " + uid;  
    return sqlDriver.update(query);
}