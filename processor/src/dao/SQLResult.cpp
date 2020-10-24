/*
 * @Author: Qizhou 
 * @Date: 2020-10-02 23:38:17 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-23 11:11:29
 */
#include "SQLResult.hpp"
#include "../../../common/myLog.h"
using im::common::logger;
using namespace im::dao;

SQLResult::SQLResult(int resultCode, std::string resultComment, MYSQL *const sqlConn, MYSQL_RES *const res)
    : _resultCode(resultCode),
      _resultComment(resultComment),
          _res(res)
{
    logger->debug("|SQLResult|constructor|start|");
    int rowNum = mysql_affected_rows(sqlConn);

    int colNum = mysql_num_fields(res);
    std::string colName[colNum];
    for (int i = 0; i < colNum; i++)
    {
        char *name = mysql_fetch_field(res)->name;
        colName[i] = name == nullptr ? "" : std::string(name);
    }

    CJsonObject dataJson;
    for (int i = 0; i < rowNum; i++)
    {
        CJsonObject colJson{};
        MYSQL_ROW rowData = mysql_fetch_row(res);
        for (int j = 0; j < colNum; j++)
        {
            string itemData = rowData[j] == nullptr ? "" : string(rowData[j]);
            colJson.Add(colName[j], itemData);
        }
        dataJson.Add(colJson);
    }
    _data = dataJson.ToString();
    logger->debug("|SQLResult|constructor|end|");
}

bool SQLResult::isSuccess()
{
    return _resultCode == 0 ? true : false;
}
SQLResult::~SQLResult()
{
    if (_res != nullptr)
    {
        mysql_free_result(_res);
    }
}

CJsonObject SQLResult::result()
{
    CJsonObject result = CJsonObject();
    result.Add("resultCode", _resultCode);
    result.Add("resultComment", _resultComment);
    return result;
}

std::string SQLResult::getData()
{
    return _data;
}