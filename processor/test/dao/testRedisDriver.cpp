/*
 * @Author: Qizhou 
 * @Date: 2020-10-03 10:00:35 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-04 08:35:15
 */
#include "../../src/dao/RedisSQLDriver.hpp"
#include "../../src/common/CJsonObject.hpp"
#include "../../src/common/Exception.hpp"
#include <assert.h>
#include <iostream>

using namespace im::dao;
using namespace std;
using im::common::Exception;

void testSQLResult() {
    std::cout << "testSQLResult" << std::endl;
    SQLResult result = SQLResult(1, "test");
    std::cout << result.result().ToFormattedString() << std::endl;
}

void testCJsonObject() {
    cout << "testCJsonObject" << endl;
    int item = 123;
    bool l;
    CJsonObject object;
    cout << object.Add("int", item) << endl;
    cout << object.ToFormattedString() << endl;
    try{
        cout << object.getBool("int", l) << endl;
    }catch(Exception e) {
        cout << e.what() << endl;
    }
}

void throwException() {
    throw im::common::Exception("test");
}

void catchException() {
    try {
        throwException();
    }catch(Exception &e) {
        cout << e.what()  << endl;
    }
}

int main() {
    RedisSQLDriver *sqldriver = RedisSQLDriver::getInstance();
    std::cout << (sqldriver->setWithExpire("testKey", "test", "10").result().ToFormattedString() ) << std::endl;
    testCJsonObject();
    CJsonObject object;
    testSQLResult();
    catchException();
    return 0;
}