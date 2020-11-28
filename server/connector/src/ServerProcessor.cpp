#include "ServerProcessor.hpp"
#include "ConnectionMapper.hpp"
#include "../../common/CJsonObject.hpp"
#include "../../common/myLog.h"
#include "MessageSender.hpp"

using namespace im;

ServerProcessor::ObjectCreator ServerProcessor::objectCreator;

ServerProcessor::ServerProcessor()
{
    mapper = ConnectionMapper::getInstance();
    logger->info("|ServerProcessor|constrcutor|end|");
}

ServerProcessor *ServerProcessor::getInstance()
{
    static ServerProcessor serverProcessor;
    return &serverProcessor;
}

void ServerProcessor::receiveData(const std::string msg)
{
    try
    {
        CJsonObject msgJson(msg);
        if (msgJson.IsEmpty())
        {
            throw common::Exception("parse json error |" + msg);
        }
        CJsonObject context = msgJson.getCJsonObject("context");
        string authToken = context.getString("authToken");
        if (mapper->findConnection(authToken))
        {
            logger->info("|ServerProcessor|receiveData|find authToken Connection|");
            TcpConnectionPtr conn = mapper->getConnection(authToken);
            if (!conn->getContext().empty() && authToken.compare(boost::any_cast<string>(conn->getContext())) == 0)
            {
                CJsonObject reponseBody;
                reponseBody.Add("data", msgJson.getCJsonObject("data"));
                reponseBody.Add("type", msgJson.getString("type"));
                reponseBody.Add("dataAck", to_string(random()));
                reponseBody.Add("dataType", "Request");
                logger->info("|ServerProcessor|receiveData|ready to send data =" + reponseBody.ToString() + "|");
                if (conn->connected())
                {
                    MessageSender::sendRequest(conn, reponseBody.ToString());
                }
                else
                {
                    throw("conn closed");
                }
            }
        }
        else
        {
            logger->info("|ServerProcerssor|receiveData|authToken Connection not found| insert into offline Msg table|");
            // todo 后期写入离线数据中
        }
    }
    catch (Exception ex)
    {
        logger->info("|ServerProcessor|receiveData|error = " + string(ex.what()) + "|");
    }
}