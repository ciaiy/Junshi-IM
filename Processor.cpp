#include "Processor.hpp"
#include "common/myLog.h"

using namespace im;

using im::common::logger;

namespace im
{
    Processor *Processor::getInstance()
    {
        static Processor processor;
        return &processor;
    }

    void Processor::process(std::string msg)
    {

    }

} // namespace im
