// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "Exception.hpp"
#include "CurrentThread.hpp"
#include <iostream>
using namespace im::common;

Exception::Exception(std::string msg)
    : message_(msg),
      stack_(CurrentThread::stackTrace(/*demangle=*/true))
{
}
