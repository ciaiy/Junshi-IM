#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

namespace im
{
    class Processor
    {
    public:
        static Processor *getInstance();
        void process(string msg);
    };
} // namespace im
#endif