#include "ServerProcessor.hpp"
#include "ConnectionMapper.hpp"
#include "../../common/CJsonObject.hpp"
#include "../../common/myLog.h"
#include "MessageSender.hpp"
#include "ConnectionMapper.hpp"

using namespace im;
using namespace im::common;

ServerProcessor::ObjectCreator ServerProcessor::objectCreator;

ServerProcessor::ServerProcessor()
{
    mapper = ConnectionMapper::getInstance();
    common::logger->info("|ServerProcessor|constrcutor|end|");
}

ServerProcessor *ServerProcessor::getInstance()
{
    static ServerProcessor serverProcessor;
    return &serverProcessor;
}

void ServerProcessor::refreshConnection(const TcpConnectionPtr &conn, CJsonObject context)
{
    try
    {
        string newToken = context.getString("uid") + ":" + context.getString("token");
        string oldToken = boost::any_cast<string>(conn->getContext());
        logger->info("|ServerProcessor|refreshConnection|conn context :" + oldToken + "new context = " + newToken);
        conn->setContext(newToken);
        ConnectionMapper::getInstance()->refreshConnection(oldToken, newToken, conn);
        logger->debug("|ServerProcessor|refreshConnectino|now conn context: " + boost::any_cast<string>(conn->getContext()) + "|");
    }
    catch (std::exception ex)
    {
        logger->error("|ServerProcessor|refreshConnection|error " + string(ex.what()) + "|");
    }
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
                string type = msgJson.getString("type");
                if (type.compare("USER_ONLINE") == 0)
                {
                    refreshConnection(conn, msgJson.getCJsonObject("context"));
                }
                reponseBody.Add("data", msgJson.getCJsonObject("data"));
                reponseBody.Add("type", type);
                if (type.compare("MSGACK") != 0)
                {
                    reponseBody.Add("dataAck", to_string(random()));
                }
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
    catch (std::exception ex)
    {
        logger->info("|ServerProcessor|receiveData|error = " + string(ex.what()) + "|");
    }
}