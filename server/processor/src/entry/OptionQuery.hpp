/*
 * @Author: Qizhou 
 * @Date: 2020-10-22 17:54:42 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-22 18:21:27
 */
#ifndef _MESSAGEQUERY_H_
#define _MESSAGEQUERY_H_

#include <string>

using std::string;
namespace im
{
    namespace entry
    {
        // 对话消息类
        class OptionQuery
        {
        private:
            // 发起请求的id
            string uid;
            // 相关cid
            string cid;
            // 操作对象id
            string optid;
            // 操作数据
            string message;
            // 操作类型
            int32_t type;
            // 冗余备用
            string ext;
            // 用户上下文
            string context;

        public:
            class Builder
            {
            public:
                string uid;
                string cid;
                string optid;
                string message;
                int32_t type;
                string ext;

                Builder *setUid(string uid)
                {
                    this->uid = uid;
                    return this;
                }
                Builder *setCid(string cid)
                {
                    this->cid = cid;
                    return this;
                }
                Builder *setMessage(string message)
                {
                    this->message = message;
                    return this;
                }
                Builder *setOptid(string optid)
                {
                    this->optid = optid;
                    return this;
                }
                Builder *setType(int32_t type)
                {
                    this->type = type;
                    return this;
                }
                Builder *setExt(string ext)
                {
                    this->ext = ext;
                    return this;
                }
                OptionQuery create()
                {
                    return OptionQuery(this);
                }
            };
            OptionQuery(string queryStr);
            class Type
            {
            public:
                const static int32_t LOGIN = 1;
                const static int32_t LOGOUT = 1 << 1;
            };

        private:
            OptionQuery(Builder *builder) : uid(builder->uid),
                                            cid(builder->cid),
                                            optid(builder->cid),
                                            message(builder->message),
                                            type(builder->type),
                                            ext(builder->ext)
            {
            }

        public:
        string getContext() {
            return this->context;
        }
            string getUid()
            {
                return this->uid;
            }

            string getCid()
            {
                return this->cid;
            }

            string getOptid()
            {
                return this->optid;
            }

            string getMessage()
            {
                return this->message;
            }

            string getExt()
            {
                return this->ext;
            }

            int32_t getType()
            {
                return this->type;
            }
        };
    } // namespace entry
} // namespace im

#endif