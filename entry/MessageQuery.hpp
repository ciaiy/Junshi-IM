/*
 * @Author: Qizhou 
 * @Date: 2020-10-12 00:01:27 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-12 00:15:01
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
        class MessageQuery
        {
        private:
            string uid;
            string cid;
            string message;
            string type;
            string ext;

        public:
            class Builder
            {
            public:
                string uid;
                string cid;
                string message;
                string type;
                string ext;

                Builder *uid(string uid)
                {
                    this->uid = uid;
                    return this;
                }
                Builder *cid(string cid)
                {
                    this->cid = cid;
                    return this;
                }
                Builder *message(string message)
                {
                    this->message = message;
                    return this;
                }
                Builder *type(string type)
                {
                    this->type = type;
                    return this;
                }
                Builder *ext(string ext)
                {
                    this->ext = ext;
                    return this;
                }
                MessageQuery create()
                {
                    return MessageQuery(this);
                }
            };

        private:
            MessageQuery(Builder *builder) : uid(builder->uid),
                                             cid(builder->cid),
                                             message(builder->message),
                                             type(builder->type),
                                             ext(builder->ext)
            {
            }

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

            string getType()
            {
                return this->type;
            }
        };
    } // namespace entry
} // namespace im

#endif