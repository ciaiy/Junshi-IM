/*
 * @Author: Qizhou 
 * @Date: 2020-12-03 03:14:25 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-12-03 03:41:46
 */
/*
 * @Author: Qizhou 
 * @Date: 2020-10-22 17:54:53 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-22 18:37:29
 */
#ifndef _MESSAGEPROCESSOR_H_
#define _MESSAGEPROCESSOR_H_
#include "../../common/SingletonPattern.hpp"
#include "dao/MysqlService.hpp"
#include "entry/MessageQuery.hpp"
#include "SenderProducer.hpp"

using namespace im;
using namespace im::common;
using namespace im::dao;
using namespace im::entry;
namespace im
{
    class MessageProcessor
    {
    public:
        MessageProcessor(SenderProducer *SenderProducer);

    private:
        MysqlService sqlService;
        SenderProducer *senderProducer;
    public:
        void process(MessageQuery query);
    };

} // namespace im

#endif