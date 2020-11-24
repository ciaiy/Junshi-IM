/*
 * @Author: Qizhou 
 * @Date: 2020-11-10 17:09:58 
 * @Last Modified by: Qizhou
 * @Last Modified time: 2020-11-10 17:57:57
 */
#include "Processor.hpp"
#include "../../common/Exception.hpp"
#include "../../common/CJsonObject.hpp"

using namespace im;
using im::common::logger;

void Processor::receiveData(const TcpConnectionPtr &conn, const std::string &msg)
{
    try
    {
        CJsonObject dataJson(msg);
        
        if(dataJson.IsEmpty()) {
            throw Exception("json parse error " + msg);
        }

        string origin = dataJson.getString("origin");
        if(ORIGIN_CLIENT.compare(origin) == 0) {
            queryProcessor->receiveData(conn, dataJson.getCJsonObject("query").ToString());
        }else if(ORIGIN_SERVER.compare(origin) == 0) {
            serverProcessor->receiveData(dataJson.getCJsonObject("query").ToString());
        }else {
            throw Exception("origin error | " + origin);
        }
    }
    catch (Exception ex)
    {
        logger->error("|Processor|receiveData|error : " + std::string(ex.what()) + "|");
    }
}