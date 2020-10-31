/*
 * @Author: Qizhou 
 * @Date: 2020-10-22 17:54:53 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-22 18:37:29
 */
#ifndef _OPTIONPROCESSOR_H_
#define _OPTIONPROCESSOR_H_
#include "../../common/SingletonPattern.hpp"
#include "dao/MysqlService.hpp"
#include "entry/OptionQuery.hpp"
#include "SenderProducer.hpp"

using namespace im;
using namespace im::common;
using namespace im::dao;
using namespace im::entry;
namespace im
{
    class OptionProcessor
    {
    public:
        OptionProcessor(SenderProducer *SenderProducer);

    private:
        MysqlService sqlService;
        SenderProducer *senderProducer;
    public:
        void process(string query);
        void dispatch(OptionQuery *optionQuery);

    private:
        void login(string optid, string message);
    };

} // namespace im

#endif