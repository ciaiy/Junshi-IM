#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include "common/SingletonPattern.hpp"

using im::common::SingtonPattern;

namespace im
{
    class Processor : SingtonPattern
    {
    public:
        static Processor *getInstance();
        void process(string msg);
    private:
        void createMessageQuery(string queryBody);
        OptionProcessor *optionProcessor;
    public:
        // 辅助代理类
        struct ObjectCreator
        {
            ObjectCreator()
            {
                Processor::getInstance();
            }
        };
        static ObjectCreator objectCreator;
    };
} // namespace im
#endif