// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H

#include <string>

namespace im
{
    namespace common
    {
        namespace CurrentThread
        {
            std::string stackTrace(bool demangle);
        } // namespace CurrentThread
    }     // namespace common
} // namespace im

#endif // MUDUO_BASE_CURRENTTHREAD_H
