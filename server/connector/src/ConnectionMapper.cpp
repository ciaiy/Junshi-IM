#include "ConnectionMapper.hpp"
#include "../../common/CurrentThread.hpp"
#include "../../common/Exception.hpp"

#include <mutex>
#include <map>

using namespace im;

ConnectionMapper::ObjectCreator ConnectionMapper::objectCreator;

ConnectionMapper *ConnectionMapper::getInstance()
{
    static ConnectionMapper mapper;
    return &mapper;
}

void ConnectionMapper::insertConnection(const TcpConnectionPtr &conn)
{
    mtx.lock();
    boost::any key = conn->getContext();
    if(key.empty()) {
        throw common::Exception("conn context null");
    }
    connectionMapper.insert(make_pair(boost::any_cast<string>(key), conn));
    mtx.unlock();
}

bool ConnectionMapper::findConnection(const std::string &key)
{

    if (connectionMapper.find(key) != connectionMapper.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

const TcpConnectionPtr ConnectionMapper::getConnection(const std::string &key)
{
    mtx.lock();
    if (findConnection(key))
    {
        mtx.unlock();
        return connectionMapper[key];
    }
    else
    {
        mtx.unlock();
        throw common::Exception("Connection not exist");
    }
}

void ConnectionMapper::deleteConneciton(const std::string key)
{
    mtx.lock();
    if (findConnection(key))
    {

        connectionMapper.erase(key);
        mtx.unlock();
    }
    else
    {
        mtx.unlock();
        throw common::Exception("Connection not exist");
    }
}
