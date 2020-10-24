#include "MysqlService.hpp"
#include "../../../common/myLog.h"
using namespace im;
using namespace im::common;
using namespace im::dao;

MysqlService::MysqlService() {
    logger->info("|MysqlService|constructor|complete|");
}

SQLResult MysqlService::getUserInfo(const std::string uid) {
    logger->debug("|MysqlService|getUserInfo|start|");
    string query = "select * from allUser where account = " + uid;
    return sqlDriver.select(query);
}