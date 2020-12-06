/*
 * @Author: Qizhou 
 * @Date: 2020-10-12 00:01:27 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-12-03 03:37:52
 */
#ifndef _MESSAGEQUERY_H_
#define _MESSAGEQUERY_H_

#include <string>
#include "../../../common/CJsonObject.hpp"
#include "../../../common/Exception.hpp"
#include "../../../common/myLog.h"

using std::string;
using namespace im::common;
namespace im
{
    namespace entry
    {
        // 对话消息类
        class MessageQuery
        {
        private:
            // 发起请求的id
            string uid;
            // 消息id
            string msgId;
            // 相关cid
            string cid;
            // 操作数据
            string message;
            // 操作类型
            int type;
            // 发送消息的用户名
            string sourceName;
            // 发送消息的uid
            string sourceUid;
            // 发送消息的来源类型
            int sourceType;
            // 冗余备用
            string ext;
            // 上下文
            CJsonObject context;

        public:
            string getUid()
            {
                return this->uid;
            }

            string getCid()
            {
                return this->cid;
            }

            string getMessage()
            {
                return this->message;
            }

            string getExt()
            {
                return this->ext;
            }

            string getSourceName()
            {
                return this->sourceName;
            }

            string getSourceUid()
            {
                return this->sourceUid;
            }

            int getSourceType()
            {
                return this->sourceType;
            }

            int getType()
            {
                return this->type;
            }

            string getMsgId() {
                return this->msgId;
            }

            CJsonObject getContext() {
                return this->context;
            }

            MessageQuery(string query);
        };
    } // namespace entry
} // namespace im

#endif