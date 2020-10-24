/*
 * @Author: Qizhou 
 * @Date: 2020-10-02 23:38:22 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-23 10:54:22
 */
#ifndef _SQLRESULT_H_
#define _SQLRESULT_H_

#include <string>
#include "../../../common/CJsonObject.hpp"
#include <mysql/mysql.h>

using im::common::CJsonObject;

namespace im
{
    namespace dao
    {
        class SQLResult
        {
        private:
            int _resultCode;
            std::string _resultComment;
            std::string _data;
            MYSQL_RES *_res;

        public:
            inline SQLResult(int resultCode, std::string resultComment)
                : _resultCode(resultCode), _resultComment(resultComment), _data(""), _res(nullptr) {}
            SQLResult(int resultCode, std::string resultComment, MYSQL *const sqlConn, MYSQL_RES *const res);
            std::string getData();
            // 返回是否成功
            virtual bool isSuccess();

            // 返回result
            // {"resultCode" : "0", "resultComment" : "comment"}
            virtual CJsonObject result();

            virtual ~SQLResult();
        };
    } // namespace dao

} // namespace im

#endif