/*
 * @Author: Qizhou 
 * @Date: 2020-10-02 23:38:17 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-04 08:25:52
 */
#include "SQLResult.hpp"

using namespace im::dao;

SQLResult::SQLResult(const SQLResult &result) {
    this->_resultCode = result._resultCode;
    this->_resultComment = result._resultCode;
}

bool SQLResult::isSuccess()
{
    return _resultCode == 0 ? true : false;
}

CJsonObject SQLResult::result() {
    CJsonObject result = CJsonObject();
    result.Add("resultCode", _resultCode);
    result.Add("resultComment", _resultComment);
    return result;
}