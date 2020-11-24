// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
#include <thread>

namespace im
{
    namespace common
    {
        class Exception : public std::exception
        {
        public:
            Exception(std::string what);
            ~Exception() = default;

            // default copy-ctor and operator= are okay.

            const char *what() 
            {
                return message_.c_str();
            }

            const char *stackTrace()  
            {
                return stack_.c_str();
            }

        private:
            std::string message_;
            std::string stack_;
        };

    } // namespace common
} // namespace im
#endif 