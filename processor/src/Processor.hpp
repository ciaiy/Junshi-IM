#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include "../../common/SingletonPattern.hpp"
#include "OptionProcessor.hpp"
using im::common::SingtonPattern;

namespace im
{
    class Processor : SingtonPattern
    {
    public:
        Processor();
        void process(string msg);

    private:
        void createMessageQuery(string queryBody);
        OptionProcessor *optionProcessor;
    };
} // namespace im
#endif