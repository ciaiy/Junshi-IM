/*
 * @Author: Qizhou 
 * @Date: 2020-10-23 10:08:18 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-12-03 04:53:26
 */
#include "MysqlSQLDriver.hpp"
#include "../../../common/myLog.h"
#include "../../../common/Exception.hpp"
#include "../../../common/config.hpp"

using namespace im;
using namespace im::common;
using namespace im::dao;

std::mutex MysqlSQLDriver::init_lock;

MysqlSQLDriver::MysqlSQLDriver()
{
    init_lock.lock();
    sqlConn = new MYSQL();
    mysql_init(sqlConn);
    try
    {
        if (sqlConn == nullptr)
        {
            throw Exception("sqlConn = nullptr");
            exit(-1);
        }
        CJsonObject config = CJsonObject(im::common::MysqlConfig);
        if (config.IsEmpty())
        {
            throw Exception("parse redisConfig error");
        }
        connect(SQLConn(config));
    }
    catch (Exception ex)
    {
        logger->error("|MysqlSQLDriver|constructor|error : " + string(ex.what()) + "|");
        init_lock.unlock();
        exit(-1);
    }
    thisThread = this_thread::get_id();
    init_lock.unlock();
    logger->info("|MysqlSQLDriver|constructor|complete|");
}
MysqlSQLDriver::~MysqlSQLDriver()
{
    mysql_close(sqlConn);
    logger->info("|MysqlSQLDriver|destructor|complete|");
}

void MysqlSQLDriver::connect(SQLConn conn)
{
    if (!mysql_real_connect(sqlConn, conn.ip().c_str(), conn.username().c_str(), conn.password().c_str(), conn.database().c_str(), 0, NULL, 0))
    {
        logger->error("|MysqlSQLDriver|connect|error " + string(mysql_error(sqlConn)) + "|");
        exit(-1);
    }
    else
    {
        logger->info("|MysqlSQLDriver|connect|connect success ");
    }
}

SQLResult MysqlSQLDriver::select(const string &query)
{
    logger->info("|MysqlDriver|select|query = " + query);
    if (mysql_query(sqlConn, query.c_str()) != 0)
    {

        string errorComment = string(mysql_error(sqlConn));
        logger->info("|MysqlSQLDriver|select|query : " + query + "| error :" + errorComment + "|");
        return SQLResult(-1, errorComment);
    }
    else
    {
        MYSQL_RES *res = mysql_store_result(sqlConn);
        return SQLResult(0, "success", sqlConn, res);
    }
}

SQLResult MysqlSQLDriver::insert(const string &query) {
    logger->info("|MysqlSQLDriver|insert|query = " + query + "|");
     if (mysql_query(sqlConn, query.c_str()) != 0)
    {
        string errorComment = string(mysql_error(sqlConn));
        logger->info("|MysqlDriver|insert|query = " + query + "| error :" + errorComment + "|");
        return SQLResult(-1, errorComment);
    }
    else
    {
        return SQLResult(0, "success");
    }
}

SQLResult MysqlSQLDriver::update(const string &query)
{
    logger->info("|MysqlDriver|update|query = " + query);
    if (mysql_query(sqlConn, query.c_str()) != 0)
    {
        string errorComment = string(mysql_error(sqlConn));
        logger->info("|MysqlDriver|update|query = " + query + "| error :" + errorComment + "|");
        return SQLResult(-1, errorComment);
    }
    else
    {
        return SQLResult(0, "success");
    }
}