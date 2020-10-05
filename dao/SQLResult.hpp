/*
 * @Author: Qizhou 
 * @Date: 2020-10-02 23:38:22 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-04 08:25:57
 */
#ifndef _SQLRESULT_H_
#define _SQLRESULT_H_

#include <string>
#include "../common/CJsonObject.hpp"

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

        public:
            SQLResult(const SQLResult &result);
            SQLResult(int resultCode, std::string resultComment)
                : _resultCode(resultCode), _resultComment(resultComment) {}

            // 返回是否成功
            virtual bool isSuccess();

            // 返回result
            // {"resultCode" : "0", "resultComment" : "comment"}
            virtual CJsonObject result();

            virtual ~SQLResult() {}
        };
    } // namespace dao

} // namespace im

#endif