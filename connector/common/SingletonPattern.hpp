#ifndef _SINGLETONPATTERN_H_
#define _SINGLETONPATTERN_H_

#include <memory>
namespace im
{
    namespace common
    {
        template <typename T>
        class SingtonPattern
        {
        public:
            virtual ~SingtonPattern() = default;
        };
    } // namespace common
} // namespace im

#endif