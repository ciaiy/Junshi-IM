#include "ServerProcessor.hpp"
#include "ConnectionMapper.hpp"
#include "../../common/CJsonObject.hpp"

using namespace im;

void ServerProcessor::receiveData(const TcpConnectionPtr &conn, const std::string msg)
{
    CJsonObject msgJson(msg);
    if (msgJson.IsEmpty())
    {
        throw common::Exception("parse json error |" + msg);
    }
    msgJson.getString();
    if (mapper->findConnection())
}