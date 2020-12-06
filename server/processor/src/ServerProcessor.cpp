/*
 * @Author: Qizhou 
 * @Date: 2020-10-22 17:54:50 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-10-31 16:39:39
 */
#include "ServerProcessor.hpp"
#include "../../common/myLog.h"
#include "../../common/Exception.hpp"
#include "entry/OptionQuery.hpp"
#include "dao/MysqlService.hpp"
#include "dao/RedisSQLDriver.hpp"
#include "../../common/CurrentThread.hpp"
#include "dao/SQLResult.hpp"

using namespace im;
using namespace im::common;
using namespace im::entry;
using namespace im::dao;

void ServerProcessor::process(string query)
{
}
void ServerProcessor::dispatch(OptionQuery *optionQuery)
{
}

void ServerProcessor::logOff(string optid, string message, string context)
{
}