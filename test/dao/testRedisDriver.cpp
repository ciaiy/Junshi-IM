/*
 * @Author: Qizhou 
 * @Date: 2020-10-03 10:00:35 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-04 08:35:15
 */
#include "../../dao/RedisSQLDriver.hpp"
#include "../../common/CJsonObject.hpp"
#include <assert.h>
#include <iostream>

using namespace im::dao;

void testSQLResult() {
    std::cout << "testSQLResult" << std::endl;
    SQLResult result = SQLResult(1, "test");
    std::cout << result.result().ToFormattedString() << std::endl;
}

int main() {
    RedisSQLDriver *sqldriver = RedisSQLDriver::getInstance();
    std::cout << (sqldriver->setWithExpire("testKey", "test", "10").result().ToFormattedString() ) << std::endl;
    testSQLResult();
}