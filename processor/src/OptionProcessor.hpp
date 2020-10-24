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
using im::common::SingtonPattern;
using im::dao::MysqlService;
namespace im
{
    class OptionProcessor : SingtonPattern
    {
    public:
        static OptionProcessor *getInstance();

        // 辅助代理类
        struct ObjectCreator
        {
            ObjectCreator()
            {
                OptionProcessor::getInstance();
            }
        };
        static ObjectCreator objectCreator;
    private:
        MysqlService sqlService;
    public:
        void process(string query);
        void dispatch(OptionQuery *optionQuery);
    private:
        void login(string optid, string message);
    };

} // namespace im

#endif