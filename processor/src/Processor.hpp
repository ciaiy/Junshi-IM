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
    };
} // namespace im
#endif