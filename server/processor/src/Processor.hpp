#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include "../../common/SingletonPattern.hpp"
#include "OptionProcessor.hpp"
#include "MessageProcessor.hpp"
#include "SenderProducer.hpp"
using im::common::SingtonPattern;

namespace im
{
    class Processor : SingtonPattern
    {
    public:
        Processor();
        void process(string msg);

    private:
        SenderProducer *senderProducer;
        OptionProcessor *optionProcessor;
        MessageProcessor *messageProcessor;
    };
} // namespace im
#endif